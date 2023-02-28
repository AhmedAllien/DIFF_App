#include <QtWidgets>

#include "diffengine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseReferenceFile();
    void browseTestFile();
    void compareFiles();
    void saveDifferences();

private:
    QLineEdit *referencePathLineEdit;
    QLineEdit *testPathLineEdit;
    QString referenceFilePath;
    QString testFilePath;
    QPushButton *referenceBrowseButton;
    QPushButton *testBrowseButton;
    QPushButton *compareButton;
    QPushButton *saveButton;
    QCheckBox* ignoreWhiteSpaceCheckBox;
    QCheckBox* ignoreCaseCheckBox;
    QTextEdit *differencesTextEdit;

    void compare(QString referencePath, QString testPath, QString &differences, bool ignoreWhiteSpace, bool ignoreCase);
};

