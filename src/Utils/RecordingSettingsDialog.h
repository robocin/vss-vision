#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>

class RecordingSettingsDialog : public QDialog {
public:
    QLineEdit *videoNameLineEdit;
    QSpinBox *fpsSpinBox;

    RecordingSettingsDialog(QWidget *parent = nullptr) : QDialog(parent) {
        this->setWindowTitle("Configurações de Gravação");

        QFormLayout *formLayout = new QFormLayout;

        std::string currentDate = QDateTime::currentDateTime().toString("dd-MM-yyyy_hh-mm-ss").toStdString();
        videoNameLineEdit = new QLineEdit(QString::fromStdString(currentDate));
        formLayout->addRow("Título da gravação:", videoNameLineEdit);

        fpsSpinBox = new QSpinBox;
        fpsSpinBox->setRange(1, 30);
        fpsSpinBox->setValue(30); // Default value
        formLayout->addRow("FPS:", fpsSpinBox);

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        QPushButton *okButton = new QPushButton("OK");
        QPushButton *cancelButton = new QPushButton("Cancelar");
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(formLayout);
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
    }
};
