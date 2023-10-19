// 源文件
#include "textFinder.h"

#include <QFile>
#include <QLayout>
#include <QPushButton>
#include <QTextStream>

TextFinder::TextFinder(QWidget *parent) : QWidget(parent) {
  initUI();
  loadTextFile();
}

TextFinder::~TextFinder() = default;

void TextFinder::initUI() {
  auto hBox = new QHBoxLayout();
  auto vBox = new QVBoxLayout();
  auto btnFind = new QPushButton("Find", this);
  m_pLineEdit = new QLineEdit(this);
  m_pTextEidt = new QTextEdit(this);

  // 设置Text Finder组件的布局为垂直布局
  setLayout(vBox);

  m_pLineEdit->setPlaceholderText("Keyword:");
  hBox->addWidget(m_pLineEdit, 2);
  hBox->addWidget(btnFind, 0);

  vBox->addLayout(hBox);
  vBox->addWidget(m_pTextEidt);

  connect(btnFind, &QPushButton::clicked, this, &TextFinder::onBtnFindClicked);
}

void TextFinder::loadTextFile() {
  QFile inputFile(":/input.txt");
  inputFile.open(QIODevice::ReadOnly);

  QTextStream in(&inputFile);
  QString line = in.readAll();
  inputFile.close();

  m_pTextEidt->setPlainText(line);
  QTextCursor cursor = m_pTextEidt->textCursor();
  cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1); // ?
}

void TextFinder::onBtnFindClicked() {
  qDebug() << "btnFind has been clicked";
  auto keyword = m_pLineEdit->text();
  m_pTextEidt->find(keyword, QTextDocument::FindWholeWords);
}