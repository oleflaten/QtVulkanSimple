#include <QGuiApplication>
#include <QVulkanInstance>
#include <QLoggingCategory>
#include "RenderWindow.h"

Q_LOGGING_CATEGORY(lcVk, "qt.vulkan")

/*The QVulkanWindow subclass reimplements the factory function QVulkanWindow::createRenderer().
This returns a new instance of the QVulkanWindowRenderer subclass.
In order to be able to access various Vulkan resources via the window object, 
a pointer to the window is passed and stored via the constructor.*/
class VulkanWindow : public QVulkanWindow
{
public:
    QVulkanWindowRenderer *createRenderer() override;
};

QVulkanWindowRenderer *VulkanWindow::createRenderer()
{
	//Makes a new instance of the RenderWindow (our Renderer) class
    return new RenderWindow(this, true); // try MSAA, when available
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

	//Setting up the Vulkan instance - using Qt's convenience wrapper
    QVulkanInstance inst;
    inst.setLayers({ "VK_LAYER_KHRONOS_validation" });
    if (!inst.create())
        qFatal("Failed to create Vulkan instance: %d", inst.errorCode());


	//Make an instance of the VulkanWindow class and set the Vulkan instance on it.
    VulkanWindow w;
    w.setVulkanInstance(&inst);

	//Set the window size and start the window.
    w.resize(1024, 768);
    w.show();

    return app.exec();
}
