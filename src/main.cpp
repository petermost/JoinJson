#include "join.hpp"
#include "clean.hpp"

#include <pera_software/aidkit/qt/core/Strings.hpp>

#include <QCoreApplication>
#include <QStringList>


using namespace std;
using namespace pera_software::aidkit::qt;

int main(int argc, char *argv[])
{
	QCoreApplication application(argc, argv);
	// Remove the actual command:
	QString command = application.arguments().at(1);
	QStringList parameters = application.arguments().mid(2);

	bool success = false;
	if (command == "join"_qs || command == "merge"_qs) {
		success = joinCompileCommands(parameters);
	} else if (command == "clean"_qs || command == "cleanup"_qs) {
		success = cleanCompileCommands(parameters);
	}
	return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}
