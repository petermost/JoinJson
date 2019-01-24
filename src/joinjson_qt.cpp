#include <QCoreApplication>
#include <QStringLiteral>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QMap>
#include <pera_software/aidkit/qt/core/Console.hpp>

// TODO: Make it more robust against wrong command line parameters
// TODO: Show progress information
// TODO: Move appendArray(), appendMap() to AidKit?

using namespace std;
using namespace pera_software::aidkit::qt;

static void appendArray(QJsonArray *target, const QJsonArray &source) {
    // If we don't append the values then a new array will be added!
    for (const QJsonValue &value : source) {
        target->append(value);
    }
}

template <typename K, typename T>
    void appendMap(QMap<K, T> *target, const QMap<K, T> &source) {
        for (auto iterator = source.begin(); iterator != source.end(); ++iterator) {
            target->insert(iterator.key(), iterator.value());
        }
    }


static const QString DIRECTORY_KEY(QStringLiteral("directory"));
static const QString COMMAND_KEY(QStringLiteral("command"));
static const QString FILE_KEY(QStringLiteral("file"));

struct CompileCommand {
    QString directory;
    QString command;
    QString file;
};

using CompileCommands = QMap<QString, CompileCommand>;

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

static CompileCommands readCompileCommands(const QString &fileName) {
    CompileCommands commands;
    QJsonArray array = readJsonArray(fileName);
    if (!array.isEmpty()) {
        for (const QJsonValue &value : array) {
            QJsonObject object = value.toObject();
            CompileCommand command = {
                object[DIRECTORY_KEY].toString(),
                object[COMMAND_KEY].toString(),
                object[FILE_KEY].toString()
            };
            commands.insert(command.file, command);
        }
    }
    return commands;
}

static bool writeCompileCommands(const QString &fileName, const CompileCommands &commands) {
    QJsonArray array;

    for (const CompileCommand &command : commands) {
        QJsonObject object = {
            { DIRECTORY_KEY, command.directory },
            { COMMAND_KEY, command.command },
            { FILE_KEY, command.file }
        };
        array.append(object);
    }
    return writeJsonArray(fileName, array);
}



int main(int argc, char *argv[]) {
	QCoreApplication application(argc, argv);
    // Remove the actual command:
    QStringList inputFileNames = application.arguments().mid(1);
    QString outputFileName = inputFileNames.takeLast();

    CompileCommands solutionCompileCommands;
	for (const QString &inputFileName : inputFileNames) {
        CompileCommands projectCompileCommands = readCompileCommands(inputFileName);
        appendMap(&solutionCompileCommands, projectCompileCommands);
	}
    return writeCompileCommands(outputFileName, solutionCompileCommands) ? EXIT_SUCCESS : EXIT_FAILURE;
}
