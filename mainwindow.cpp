#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create UI elements
    setWindowTitle("Diff Program");
    referencePathLineEdit = new QLineEdit(this);
    testPathLineEdit = new QLineEdit(this);
    differencesTextEdit = new QTextEdit(this);
    differencesTextEdit->setReadOnly(true);

    referenceBrowseButton = new QPushButton("Browse...", this);
    testBrowseButton = new QPushButton("Browse...", this);
    compareButton = new QPushButton("Compare", this);
    saveButton = new QPushButton("Save Differences", this);
    ignoreWhiteSpaceCheckBox = new QCheckBox("Ignore white space");
    ignoreCaseCheckBox = new QCheckBox("Ignore case");

    // Create layouts
    QHBoxLayout *referenceLayout = new QHBoxLayout;
    referenceLayout->addWidget(referencePathLineEdit);
    referenceLayout->addWidget(referenceBrowseButton);

    QHBoxLayout *testLayout = new QHBoxLayout;
    testLayout->addWidget(testPathLineEdit);
    testLayout->addWidget(testBrowseButton);

    QVBoxLayout *fileLayout = new QVBoxLayout;
    fileLayout->addLayout(referenceLayout);
    fileLayout->addLayout(testLayout);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(compareButton);
    buttonLayout->addWidget(saveButton);

    QVBoxLayout* optionsLayout = new QVBoxLayout;
    optionsLayout->addWidget(ignoreWhiteSpaceCheckBox);
    optionsLayout->addWidget(ignoreCaseCheckBox);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(optionsLayout);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(mainLayout);
    centralLayout->addWidget(differencesTextEdit);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);

    setCentralWidget(centralWidget);

    // Connect signals and slots
    connect(referenceBrowseButton, &QPushButton::clicked, this, &MainWindow::browseReferenceFile);
    connect(testBrowseButton, &QPushButton::clicked, this, &MainWindow::browseTestFile);
    connect(compareButton, &QPushButton::clicked, this, &MainWindow::compareFiles);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveDifferences);
}

MainWindow::~MainWindow()
{
}

void MainWindow::browseReferenceFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Reference File"));
    if (!fileName.isEmpty()) {
        referencePathLineEdit->setText(fileName);
        referenceFilePath = fileName;
    }
}

void MainWindow::browseTestFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Test File"));
    if (!fileName.isEmpty()) {
        testPathLineEdit->setText(fileName);
        testFilePath = fileName;
    }
}

void MainWindow::compareFiles() {
    if (referenceFilePath.isEmpty() || testFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Please select both reference and test files."));
        return;
    }
    QString differences;
    bool ignoreWhiteSpace = ignoreWhiteSpaceCheckBox->isChecked();
    bool ignoreCase = ignoreCaseCheckBox->isChecked();
    compare(referenceFilePath, testFilePath, differences, ignoreWhiteSpace, ignoreCase);
    differencesTextEdit->setText(differences);
}

void MainWindow::compare(QString refFilePath, QString testFilePath, QString& diffOutput, bool ignoreWhiteSpace, bool ignoreCase)
{
    QFile refFile(refFilePath);
    QFile testFile(testFilePath);

    if (!refFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        diffOutput = "Error: Could not open reference file.";
        return;
    }

    if (!testFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        diffOutput = "Error: Could not open test file.";
        return;
    }

    QTextStream refStream(&refFile);
    QTextStream testStream(&testFile);

    QString refLine = refStream.readLine();
    QString testLine = testStream.readLine();
    int lineNum = 1;

    while (!refLine.isNull() || !testLine.isNull()) {

        // Ignore whitespace and/or case
        if (ignoreWhiteSpace) {
            refLine = refLine.simplified();
            testLine = testLine.simplified();
        }
        if (ignoreCase) {
            refLine = refLine.toLower();
            testLine = testLine.toLower();
        }

        if (refLine != testLine) {
            diffOutput += QString("Line %1:\n").arg(lineNum);
            diffOutput += QString("Reference: %1\n").arg(refLine);
            diffOutput += QString("Test: %1\n").arg(testLine);
            diffOutput += "\n";
        }
        refLine = refStream.readLine();
        testLine = testStream.readLine();
        lineNum++;
    }

    refFile.close();
    testFile.close();

    if (diffOutput.isEmpty()) {
        diffOutput = "Files are identical.";
    }
}

void MainWindow::saveDifferences() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Differences"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile outputFile(fileName);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        return;
    }

    QTextStream outStream(&outputFile);
    outStream << differencesTextEdit->toPlainText();
    outputFile.close();
}
