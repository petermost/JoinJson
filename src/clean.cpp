#include "clean.hpp"
#include "CompileCommands.hpp"

#include <pera_software/aidkit/qt/core/Strings.hpp>

using namespace pera_software::aidkit::qt;

bool cleanCompileCommands(const QStringList &parameters)
{
	QString inputFileName = parameters.at(0);
	QString outputFileName = parameters.at(1);

	return cleanCompileCommands(inputFileName, outputFileName);
}

bool cleanCompileCommands(const QString &inputFileName, const QString &outputFileName)
{
	CompileCommands compileCommands;
	compileCommands.read(inputFileName);
	compileCommands.forEach([](CompileCommand *command) {
		command->command = command->command.replace('/'_qc, '-'_qc);
	});

	compileCommands.write(outputFileName);

	return false;
}
