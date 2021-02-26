#include "CompileCommands.hpp"

#include <pera_software/aidkit/qt/core/Strings.hpp>

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// TODO: Show progress information

using namespace std;
using namespace pera_software::aidkit::qt;

static const QString DIRECTORY_KEY(QStringLiteral("directory"));
static const QString COMMAND_KEY(QStringLiteral("command"));
static const QString FILE_KEY(QStringLiteral("file"));


//static void appendArray(QJsonArray *target, const QJsonArray &source) {
//    // If we don't append the values then a new array will be added!
//    for (const QJsonValue &value : source) {
//        target->append(value);
//    }
//}

template <typename K, typename T>
	void appendMap(QMap<K, T> *target, const QMap<K, T> &source)
	{
		for (auto iterator = source.begin(); iterator != source.end(); ++iterator) {
			target->insert(iterator.key(), iterator.value());
		}
	}

size_t CompileCommands::read(QIODevice *inputDevice)
{
	QJsonArray array = QJsonDocument::fromJson(inputDevice->readAll()).array();

	if (!array.isEmpty()) {
		for (const QJsonValue &value : qAsConst(array)) {
			QJsonObject object = value.toObject();
			CompileCommand command = {
				.directory = object[DIRECTORY_KEY].toString(),
				.command = object[COMMAND_KEY].toString(),
				.file = object[FILE_KEY].toString()
			};
			this->insertMulti(command.file, command);
		}
	}
	return static_cast<size_t>(array.size());
}

size_t CompileCommands::read(const QString &inputFileName)
{
	QFile inputFile(inputFileName);
	if (inputFile.open(QFile::ReadOnly)) {
		return read(&inputFile);
	} else {
		return 0;
	}
}

size_t CompileCommands::write(QIODevice *outputDevice) const
{
	QJsonArray array;

	for (const CompileCommand &command : *this) {
		QJsonObject object = {
			{ DIRECTORY_KEY, command.directory },
			{ COMMAND_KEY, command.command },
			{ FILE_KEY, command.file }
		};
		array.append(object);
	}
	QJsonDocument jsonDocument(array);
	outputDevice->write(jsonDocument.toJson());

	return static_cast<size_t>(array.size());
}

size_t CompileCommands::write(const QPath &outputFileName) const
{
	QFile outputFile(outputFileName);
	if (outputFile.open(QFile::WriteOnly | QFile::Truncate)) {
		return write(&outputFile);
	} else {
		return 0;
	}
}

void CompileCommands::forEach(const function<void (CompileCommand *)> &consumer)
{
	for (auto &compileCommand : *this) {
		consumer(&compileCommand);
	}
}
