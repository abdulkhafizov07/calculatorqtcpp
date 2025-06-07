#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QJSEngine>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  setWindowTitle("Calculator App");
  resize(280, 360);
  setFixedSize(280, 400);

  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  centralWidget->setStyleSheet(
      ".QWidget {"
      "background-color: #1a1b26;"
      "}");

  QGridLayout *grid = new QGridLayout(centralWidget);
  grid->setSpacing(1);

  // Assign to the member variable, not a local variable!
  input = new QLineEdit();
  input->setReadOnly(true);
  input->setAlignment(Qt::AlignRight);
  input->setFixedHeight(40);
  input->setStyleSheet(
      ".QLineEdit {"
      "  background-color: #1a1b26;"
      "  color: #c0caf5;"
      "  border: 0;"
      "}");
  input->setFont(QFont("Roboto Mono", 24));
  grid->addWidget(input, 0, 0, 1, 4);

  const char *buttons[5][4] = {
      {"AC", " ", "C", "/"},
      {"7", "8", "9", "*"},
      {"4", "5", "6", "-"},
      {"1", "2", "3", "+"},
      {"0", ".", "=", " "}};

  for (int row = 0; row < 5; ++row)
  {
    for (int col = 0; col < 4; ++col)
    {
      if (!(QString(buttons[row][col]) == " "))
      {
        QPushButton *btn = new QPushButton(buttons[row][col]);
        btn->setFixedSize(50, 50);

        if (QString(buttons[row][col]) == "=")
        {
          btn->setStyleSheet(
              "QPushButton {"
              "  background-color: #7aa2f7;"
              "  color: #1a1b26;"
              "  font-size: 18px;"
              "  border-radius: 5px;"
              "  border: 1px solid #5c7eae;"
              "}"
              "QPushButton:hover {"
              "  background-color: #82aaff;"
              "  border: 1px solid #82aaff;"
              "}"
              "QPushButton:pressed {"
              "  background-color: #5c7eae;"
              "  border: 1px solid #3a4a7a;"
              "}");
        }
        else if (QString(buttons[row][col]) == "+" ||
                 QString(buttons[row][col]) == "-" ||
                 QString(buttons[row][col]) == "*" ||
                 QString(buttons[row][col]) == "/")
        {
          btn->setStyleSheet(
              "QPushButton {"
              "  background-color: #bb9af7;"
              "  color: #1a1b26;"
              "  font-size: 18px;"
              "  border-radius: 5px;"
              "  border: 1px solid #8f74d0;"
              "}"
              "QPushButton:hover {"
              "  background-color: #c6a0f6;"
              "  border: 1px solid #c6a0f6;"
              "}"
              "QPushButton:pressed {"
              "  background-color: #8f74d0;"
              "  border: 1px solid #6f55a0;"
              "}");
        }
        else
        {
          btn->setStyleSheet(
              "QPushButton {"
              "  background-color: #394b70;"
              "  color: #c0caf5;"
              "  font-size: 18px;"
              "  border-radius: 5px;"
              "  border: 1px solid #565f89;"
              "}"
              "QPushButton:hover {"
              "  background-color: #515f9a;"
              "  border: 1px solid #7a86b6;"
              "}"
              "QPushButton:pressed {"
              "  background-color: #2a2f45;"
              "  border: 1px solid #3b416f;"
              "}");
        }
        btn->setFont(QFont("Roboto Mono", 16));

        connect(btn, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
        QString btnLabel = QString(buttons[row][col]);

        if (btnLabel == "AC" || btnLabel == "=")
        {
          btn->setMaximumWidth(500);
          btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
          grid->addWidget(btn, row + 1, col, 1, 2);
          ++col;
        }
        else
        {
          grid->addWidget(btn, row + 1, col);
        }
      }
    }
  }
}
void MainWindow::onButtonClicked()
{
  QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
  if (clickedBtn)
  {
    QString btnText = clickedBtn->text();
    QString inputText = input->text();

    if (inputText.contains("Error") || btnText == "AC" || inputText.contains("undefined"))
    {
      input->setText("");
      inputText = "";
    }

    if (btnText == "C" && inputText.length())
    {
      inputText = inputText.slice(0, inputText.length() - 1);
      input->setText(inputText);
    }

    if (btnText == "=")
    {
      QJSEngine engine;
      QJSValue result = engine.evaluate(inputText);
      if (!result.isError())
      {
        input->setText(result.toString());
      }
      else
      {
        input->setText("Error");
      }
    }
    else if (QString("+-*/.").contains(btnText) && !inputText.isEmpty())
    {
      QChar lastChar = inputText.right(1)[0];
      if (QString("+-*/.").contains(lastChar))
      {
        input->setText(inputText.left(inputText.length() - 1) + btnText);
      }
      else
      {
        input->setText(inputText + btnText);
      }
    }
    else if (QString("1234567890").contains(btnText))
    {
      input->setText(inputText + btnText);
    }
  }
}

MainWindow::~MainWindow()
{
}
