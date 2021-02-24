#include "join.hpp"

#include <QCoreApplication>
#include <QStringList>
#include <pera_software/aidkit/qt/core/Strings.hpp>

using namespace std;
using namespace pera_software::aidkit::qt;

int main(int argc, char *argv[])
{
	QCoreApplication application(argc, argv);
	// Remove the actual command:
	QString command = application.arguments().at(1);
	QStringList parameters = application.arguments().mid(2);

	if (command == "join"_qs || command == "merge"_qs) {
		return joinCompileCommands(parameters);
	} else if (command == "clean"_qs || command == "cleanup"_qs) {

	}
}
