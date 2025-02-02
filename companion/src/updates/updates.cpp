/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "updates.h"
#include "updateinterface.h"
#include "updatesdialog.h"
#include "progressdialog.h"
#include "progresswidget.h"
#include "appdata.h"
#include "helpers.h"

#include <QMessageBox>

Updates::Updates(QWidget * parent, UpdateFactories * updateFactories) :
  QWidget(parent),
  factories(updateFactories)
{
}

Updates::~Updates()
{
}

void Updates::checkForUpdates(bool manual)
{
  if (!manual) {
    if (g.updateCheckFreq() == AppData::UPDATE_CHECK_MANUAL)
      return;

    if (g.lastUpdateCheck().trimmed().isEmpty())
      g.lastUpdateCheck(QDateTime::currentDateTime().addDays(-60).toString(Qt::ISODate));

    QDateTime dt = QDateTime::fromString(g.lastUpdateCheck(), Qt::ISODate);

    if (g.updateCheckFreq() == AppData::UPDATE_CHECK_DAILY)
      dt = dt.addDays(1);
    else if (g.updateCheckFreq() == AppData::UPDATE_CHECK_WEEKLY)
      dt = dt.addDays(7);
    else if (g.updateCheckFreq() == AppData::UPDATE_CHECK_MONTHLY)
      dt = dt.addDays(30);

    if (dt > QDateTime::currentDateTime().toLocalTime()) {
      qDebug() << "Update next due:" << dt.toString(Qt::ISODate);
      return;
    }
  }

  g.lastUpdateCheck(QDateTime::currentDateTime().toString(Qt::ISODate));

  QStringList list;

  if (!factories->isUpdatesAvailable(list)) {
    if (manual)
      QMessageBox::information(parentWidget(), CPN_STR_APP_NAME, tr("No updates available at this time"));
    return;
  }

  if (QMessageBox::question(parentWidget(), CPN_STR_APP_NAME % ": " % tr("Checking for Updates"),
                            tr("Updates available for:\n  %1\n\nUpdate now?").arg(list.join("\n  ")),
                            (QMessageBox::Yes | QMessageBox::No), QMessageBox::No) == QMessageBox::Yes) {
    doUpdates();
  }
}

void Updates::doUpdates()
{
  if (factories->sortedComponentsList(true).isEmpty()) {
    QMessageBox::warning(this, CPN_STR_APP_NAME, tr("No components have been flagged to check in Update Settings!"));
    return;
  }

  factories->resetAllRunEnvironments();

  UpdatesDialog *dlg = new UpdatesDialog(this, factories);

  bool ok = false;

  if (dlg->exec()) {
    ProgressDialog progressDialog(this, tr("Update Components"), CompanionIcon("fuses.png"), true);
    progressDialog.progress()->lock(true);
    progressDialog.progress()->setInfo(tr("Starting..."));
    ok = factories->manualUpdate(progressDialog.progress());
    progressDialog.progress()->lock(false);
    progressDialog.progress()->setInfo(tr("Finished %1").arg(ok ? tr("successfully") : tr("with errors")));
    progressDialog.exec();
  }

  delete dlg;

  if (ok)
    checkRunSDSync();
}

void Updates::checkRunSDSync()
{
  if (!g.currentProfile().runSDSync())
    return;

  if (QMessageBox::question(this, CPN_STR_APP_NAME, tr("Run SD card sync now?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    emit runSDSync();
}
