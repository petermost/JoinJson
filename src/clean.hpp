#pragma once

class QString;
class QStringList;

bool cleanCompileCommands(const QStringList &parameters);
bool cleanCompileCommands(const QString &inputFileName, const QString &outputFileName);
