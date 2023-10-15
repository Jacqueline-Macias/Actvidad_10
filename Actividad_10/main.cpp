#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <iostream>
#include <QVBoxLayout>

class Neurona {
public:
    Neurona(int id, double voltaje, int posX, int posY, int red, int green, int blue)
        : id(id), voltaje(voltaje), posX(posX), posY(posY), red(red), green(green), blue(blue) {
    }

    void print() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Voltaje: " << voltaje << std::endl;
        std::cout << "Posición X: " << posX << std::endl;
                std::cout << "Posición Y: " << posY << std::endl;
                         std::cout << "RGB: (" << red << ", " << green << ", " << blue << ")" << std::endl;
    }

    int getId() const { return id; }
    double getVoltaje() const { return voltaje; }
    int getPosX() const { return posX; }
    int getPosY() const { return posY; }
    int getRed() const { return red; }
    int getGreen() const { return green; }
    int getBlue() const { return blue; }

private:
    int id;
    double voltaje;
    int posX;
    int posY;
    int red;
    int green;
    int blue;
};

class AdministradorNeuronas {
public:
    void agregarInicio(const Neurona& neurona) {
        neuronas.insert(neuronas.begin(), neurona);
    }

    void agregarFinal(const Neurona& neurona) {
        neuronas.push_back(neurona);
    }

    const std::vector<Neurona>& getNeuronas() const {
        return neuronas;
    }

    void borrarNeuronas() {
        neuronas.clear();
    }

    void guardarNeuronas(const std::string& fileName) const {
        std::ofstream file(fileName);

        if (file.is_open()) {
            for (const Neurona& neurona : neuronas) {
                file << neurona.getId() << " "
                     << neurona.getVoltaje() << " "
                     << neurona.getPosX() << " "
                     << neurona.getPosY() << " "
                     << neurona.getRed() << " "
                     << neurona.getGreen() << " "
                     << neurona.getBlue() << std::endl;
            }
            file.close();
        }
    }

    void cargarNeuronas(const std::string& fileName) {
        std::ifstream file(fileName);

        if (file.is_open()) {
            borrarNeuronas();

            int id, posX, posY, red, green, blue;
            double voltaje;

            while (file >> id >> voltaje >> posX >> posY >> red >> green >> blue) {
                Neurona neurona(id, voltaje, posX, posY, red, green, blue);
                agregarFinal(neurona);
            }

            file.close();
        }
    }

private:
    std::vector<Neurona> neuronas;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Administrador de Neuronas");

        QPushButton *agregarInicioButton = new QPushButton("Agregar al Inicio", this);
        QPushButton *agregarFinalButton = new QPushButton("Agregar al Final", this);
        QPushButton *mostrarButton = new QPushButton("Mostrar Neuronas", this);
        QPushButton *guardarButton = new QPushButton("Guardar Neuronas", this);
        QPushButton *cargarButton = new QPushButton("Cargar Neuronas", this);
        plainTextEdit = new QPlainTextEdit(this);

        administrador = new AdministradorNeuronas;

        connect(agregarInicioButton, &QPushButton::clicked, this, &MainWindow::agregarNeuronaAlInicio);
        connect(agregarFinalButton, &QPushButton::clicked, this, &MainWindow::agregarNeuronaAlFinal);
        connect(mostrarButton, &QPushButton::clicked, this, &MainWindow::mostrarNeuronas);
        connect(guardarButton, &QPushButton::clicked, this, &MainWindow::guardarNeuronas);
        connect(cargarButton, &QPushButton::clicked, this, &MainWindow::cargarNeuronas);

        setCentralWidget(plainTextEdit);

        // Layout
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(agregarInicioButton);
        layout->addWidget(agregarFinalButton);
        layout->addWidget(mostrarButton);
        layout->addWidget(guardarButton);
        layout->addWidget(cargarButton);
        layout->addWidget(plainTextEdit);

        QWidget *widget = new QWidget(this);
        widget->setLayout(layout);
        setCentralWidget(widget);
    }

private slots:
    void agregarNeuronaAlInicio() {

        int id = 1; // Reemplaza esto con la lógica para obtener el ID desde un widget
        double voltaje = 2.0; // Reemplaza esto con la lógica para obtener el voltaje desde un widget
        int posX = 3; // Reemplaza esto con la lógica para obtener la posición X desde un widget
        int posY = 4; // Reemplaza esto con la lógica para obtener la posición Y desde un widget
        int red = 255; // Reemplaza esto con la lógica para obtener el valor rojo desde un widget
        int green = 0; // Reemplaza esto con la lógica para obtener el valor verde desde un widget
        int blue = 0; // Reemplaza esto con la lógica para obtener el valor azul desde un widget

        Neurona neurona(id, voltaje, posX, posY, red, green, blue);
        administrador->agregarInicio(neurona);
    }

    void agregarNeuronaAlFinal() {
    }

    void mostrarNeuronas() {
        plainTextEdit->clear();
        const std::vector<Neurona>& neuronas = administrador->getNeuronas();
        for (const Neurona& neurona : neuronas) {
            neurona.print();
        }
    }

    void guardarNeuronas() {
        QString fileName = QFileDialog::getSaveFileName(this, "Guardar Neuronas", "", "Archivos de Texto (*.txt)");
        if (!fileName.isEmpty()) {
            administrador->guardarNeuronas(fileName.toStdString());
        }
    }

    void cargarNeuronas() {
        QString fileName = QFileDialog::getOpenFileName(this, "Cargar Neuronas", "", "Archivos de Texto (*.txt)");
        if (!fileName.isEmpty()) {
            administrador->cargarNeuronas(fileName.toStdString());
        }
    }

private:
    QPlainTextEdit *plainTextEdit;
    AdministradorNeuronas *administrador;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

private slots:
void ordenarNeuronasPorId() {
    std::vector<Neurona>& neuronas = administrador->getNeuronas();
    std::sort(neuronas.begin(), neuronas.end(), [](const Neurona& a, const Neurona& b) {
        return a.getId() < b.getId();
    });
    mostrarNeuronas();
}

void ordenarNeuronasPorVoltaje() {
    std::vector<Neurona>& neuronas = administrador->getNeuronas();
    std::sort(neuronas.begin(), neuronas.end(), [](const Neurona& a, const Neurona& b) {
        return a.getVoltaje() < b.getVoltaje();
    });
    mostrarNeuronas();
}
