// 头文件
#ifndef _TEXTFINDER_H_
#define _TEXTFINDER_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>

class TextFinder : public QWidget {
  Q_OBJECT
public:
  TextFinder(QWidget *parent = nullptr);
  ~TextFinder();

private:
  QTextEdit *m_pTextEidt;
  QLineEdit *m_pLineEdit;

  /**
   * @brief 初始化UI
   *
   */
  void initUI();

  /**
   * @brief 加载文本文件
   *
   */
  void loadTextFile();

private slots:
  void onBtnFindClicked();
};

#endif // _TEXTFINDER_H_