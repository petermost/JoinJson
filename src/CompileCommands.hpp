#pragma once

#include <QMap>

#include <functional>

class QIODevice;

using QPath = QString;

struct CompileCommand {
	QPath directory;
	QString command;
	QPath file;
};

class CompileCommands : public QMap<QPath, CompileCommand> {
	public:
		size_t read(const QPath &inputFileName);
		size_t read(QIODevice *inputDevice);

		size_t write(const QPath &outputFileName) const;
		size_t write(QIODevice *outputDevice) const;

		void forEach(const std::function<void (CompileCommand *)> &consumer);
};
