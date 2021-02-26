#include "join.hpp"
#include "CompileCommands.hpp"
#include <pera_software/aidkit/qt/core/Console.hpp>

using namespace pera_software::aidkit::qt;

// TODO: Make it more robust against wrong command line parameters
// TODO: Move appendArray(), appendMap() to AidKit?

using namespace std;

bool joinCompileCommands(const QStringList &parameters)
{
	QStringList inputFileNames = parameters.mid(0, parameters.length() - 1);
	QString outputFileName = parameters.last();

	return joinCompileCommands(inputFileNames, outputFileName);
}

bool joinCompileCommands(const QStringList &inputFileNames, const QString &outputFileName)
{
	size_t count;
	CompileCommands compileCommands;

	for (const QString &inputFileName : inputFileNames) {
		cout << "Reading file '" << inputFileName << "' ..." << endl;
		count = compileCommands.read(inputFileName);
		if (count > 0) {
			cout << "File '" << inputFileName << "' read " << count << " entries." << endl;
		} else {
			cerr << "File '" << inputFileName << "' could not be open for reading!" << endl;
		}
	}
	cout << "Writing file '" << outputFileName << "' ..." << endl;
	count = compileCommands.write(outputFileName);
	if (count > 0) {
		cout << "File '" << outputFileName << "' written " << count << " entries." << endl;
	} else {
		cerr << "File '" << outputFileName << "' could not be open for writing!" << endl;
	}
	return count > 0;
}

