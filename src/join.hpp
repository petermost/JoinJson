#pragma once

class QString;
class QStringList;

bool joinCompileCommands(const QStringList &parameters);
bool joinCompileCommands(const QStringList &inputFileNames, const QString &outputFileName);
