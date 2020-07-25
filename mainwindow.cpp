#include "mainwindow.hh"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  /// Initialize Scenes
  scene_ = new QGraphicsScene(this);
  nextScene_ = new QGraphicsScene(this);
  holdScene_ = new QGraphicsScene(this);

  ui->graphicsView->setScene(scene_);
  ui->nextView->setScene(nextScene_);
  ui->holdView->setScene(holdScene_);

  scene_->setSceneRect(0, 0, BORDER_RIGHT, BORDER_DOWN);
  nextScene_->setSceneRect(0, 0, SMALL_BORDER_RIGHT, SMALL_BORDER_DOWN);
  holdScene_->setSceneRect(0, 0, SMALL_BORDER_RIGHT, SMALL_BORDER_DOWN);

  int seed = time(0);
  randomEng.seed(seed);
  distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
  distr(randomEng);

  timer.setInterval(333);

  connect(&timer, &QTimer::timeout, this, &MainWindow::tick);
  connect(this, &MainWindow::setScore, ui->score,
          qOverload<int>(&QLCDNumber::display));

  nextTetrominion_ = new Tetromino(TetrominoType(distr(randomEng)), this,
                                   Coords(SMALL_BORDER_RIGHT / BLOCK / 2 - 2,
                                          SMALL_BORDER_DOWN / BLOCK / 2 - 1));
  renderTetromino(nextTetrominion_, nextScene_);

  ui->stopButton->setDisabled(true);
  ui->graphicsView->show();
}

MainWindow::~MainWindow() {
  for (Block block : blocks_) {
    delete block;
  }

  delete nextTetrominion_;

  if (tetrominion_ != nullptr) {
    delete tetrominion_;
  }

  if (holdTetrominion_ != nullptr) {
    delete holdTetrominion_;
  }

  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_D:
      move(RIGHT);
      break;

    case Qt::Key_A:
      move(LEFT);
      break;

    case Qt::Key_E:
      rotate(1);
      break;

    case Qt::Key_Q:
      rotate(-1);
      break;

    case Qt::Key_S:
      tick();
      break;

    case Qt::Key_X:
      fallDown();
      break;

    case Qt::Key_W:
      takeHold();
      break;

    default:
      return;
  }
}

void MainWindow::renderTetromino(Tetromino *tetro, QGraphicsScene *scene,
                                 SceneType type) {
  if (type == HOLD) {
    for (Block block : tetro->blocks()) {
      blocks_.erase(std::find(blocks_.begin(), blocks_.end(), block));
    }
  }

  tetro->render();
  for (Block block : tetro->blocks()) {
    scene->addItem(block);
    if (type == MAIN) {
      blocks_.push_back(block);
    }
  }
}

void MainWindow::tick() {
  if (tetrominion_ == nullptr) {
    tetrominion_ = nextTetrominion_;
    tetrominion_->setPos(Coords(TETRO_CENTER, 0));
    renderTetromino(tetrominion_, scene_, MAIN);

    nextTetrominion_ = new Tetromino(TetrominoType(distr(randomEng)), this,
                                     Coords(SMALL_BORDER_RIGHT / BLOCK / 2 - 2,
                                            SMALL_BORDER_DOWN / BLOCK / 2 - 1));
    renderTetromino(nextTetrominion_, nextScene_);

    if (!tetrominion_->moveTo(Coords(0, 0))) {
      gameOver();
    }
  }

  if (!tetrominion_->moveTo(DOWN)) {
    delete tetrominion_;
    tetrominion_ = nullptr;

    justReleased_ = false;
    checkRows();
  }
}

void MainWindow::on_startButton_clicked() {
  timer.start();
  ui->startButton->setDisabled(true);
  ui->stopButton->setEnabled(true);
  ui->stopButton->setText("STOP");
}

std::vector<Block> MainWindow::blocks() const { return blocks_; }

void MainWindow::on_stopButton_clicked() {
  timer.stop();
  ui->startButton->setEnabled(true);
  ui->stopButton->setDisabled(true);
  ui->stopButton->setText("CONTINUE");
}

void MainWindow::move(const Directions &direction) {
  if (tetrominion_ != nullptr) {
    tetrominion_->moveTo(direction);
  }
}

void MainWindow::rotate(const int &direction) {
  if (tetrominion_ != nullptr) {
    tetrominion_->rotateIfAble(direction);
  }
}

void MainWindow::takeHold() {
  if (!justReleased_ && tetrominion_ != nullptr) {
    Tetromino *temp = holdTetrominion_;
    holdTetrominion_ = tetrominion_;
    holdTetrominion_->setPos(Coords(SMALL_BORDER_RIGHT / BLOCK / 2 - 2,
                                    SMALL_BORDER_DOWN / BLOCK / 2 - 1));
    renderTetromino(holdTetrominion_, holdScene_, HOLD);

    tetrominion_ = temp;
    if (tetrominion_ != nullptr) {
      tetrominion_->setPos(Coords(TETRO_CENTER, 0));
      renderTetromino(tetrominion_, scene_, MAIN);
    }

    justReleased_ = true;
  }
}

void MainWindow::checkRows() {
  std::vector<int> rowSums(ROWS, 0);
  for (Block block : blocks_) {
    int y = block->gridPos().y;
    rowSums.at(y) += 1;
  }

  int amountOfRows = 0;
  for (unsigned int i = 0; i < rowSums.size(); i++) {
    int sum = rowSums.at(i);
    if (sum == COLUMNS) {
      deleteRow(i);
      amountOfRows += 1;
    }
  }

  int baseScore = amountOfRows * SCORE;
  int extraScore = amountOfRows * SCORE / 2;

  score_ = score_ + baseScore + extraScore;
  emit setScore(score_);

  if (amountOfRows == 4) {
    tetrisCount_ += 1;
    ui->tetrisCount->setText("Tetris count: " + QString::number(tetrisCount_));
  }
}

void MainWindow::fallDown() {
  if (tetrominion_ != nullptr) {
    while (tetrominion_->moveTo(DOWN)) {
      continue;
    }
  }
}

void MainWindow::gameOver() {
  timer.stop();
  QMessageBox msgBox;

  msgBox.setText("GAME OVER :(");

  QPushButton *quitButton = msgBox.addButton(QMessageBox::Ok);
  quitButton->setMinimumSize(60, 30);

  msgBox.exec();

  if (msgBox.clickedButton() == quitButton) {
    close();
  }
}

void MainWindow::deleteRow(const int &y) {
  blocks_.erase(std::remove_if(blocks_.begin(), blocks_.end(),
                               [y](Block p) {
                                 if (p->gridPos().y == y) {
                                   delete p;
                                   return true;
                                 }
                                 return false;
                               }),
                blocks_.end());
  for (Block block : blocks_) {
    if (block->gridPos().y < y) {
      block->move(Coords(DOWN));
    }
  }
}
