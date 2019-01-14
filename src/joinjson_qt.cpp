#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <pera_software/aidkit/qt/core/Console.hpp>
#include <optional>

using namespace std;
using namespace pera_software::aidkit::qt;

static QJsonArray readJsonArray(const QString &fileName) {
	QJsonArray jsonArray;

	QFile inputFile(fileName);
	if (inputFile.open(QFile::ReadOnly)) {
		jsonArray = QJsonDocument::fromJson(inputFile.readAll()).array();
	} else {
		cerr << "File '" << fileName << "' could not be open for reading!" << endl;
	}
	return jsonArray;
}

static bool writeJsonArray(const QString &fileName, const QJsonArray &jsonArray) {
	QFile outputFile(fileName);
	if (outputFile.open(QFile::WriteOnly | QFile::Truncate)) {
		QJsonDocument jsonDocument(jsonArray);
		outputFile.write(jsonDocument.toJson());
		return true;
	} else {
		cerr << "File '" << fileName << "' could not be open for writing!" << endl;
		return false;
	}
}

static void appendArray(QJsonArray *target, const QJsonArray &source) {
	// If we don't append the values then a new array will be added!
	for (const QJsonValue &value : source) {
		target->append(value);
	}
}

int main(int argc, char *argv[]) {
	QCoreApplication application(argc, argv);
	QStringList inputFileNames = application.arguments();
	// Remove the command line:
	inputFileNames.removeFirst();

	QJsonArray compileCommands;
	for (const QString &inputFileName : inputFileNames) {
		appendArray(&compileCommands, readJsonArray(inputFileName));
	}
	return writeJsonArray("compile_commands.json", compileCommands) ? EXIT_SUCCESS : EXIT_FAILURE;
}
