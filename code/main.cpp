#include <QApplication>

#include "core/controllers/AppController.h"
#include "core/data/JsonContentRepository.h"
#include "core/data/JsonProfileRepository.h"
#include "ui/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    JsonContentRepository contentRepository;
    JsonProfileRepository profileRepository;

    AppController controller(&contentRepository, &profileRepository);
    controller.initialize();

    MainWindow window(&controller);
    window.show();

    return app.exec();
}
