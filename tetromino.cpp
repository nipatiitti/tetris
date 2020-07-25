#include "tetromino.hh"

#include <QDebug>

#include "mainwindow.hh"

Tetromino::Tetromino(const TetrominoType& type, MainWindow* w, Coords pos)
    : pos_(pos), w_(w), type_(type) {
  /// Set the shape and background image according the type
  switch (type) {
    case HORIZONTAL:
      SIZE_X = 4;
      SIZE_Y = 4;
      background_ = QPixmap(":/cyan");
      shape_ = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
      break;
    case LEFT_CORNER:
      background_ = QPixmap(":/blue");
      shape_ = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}};
      break;
    case RIGHT_CORNER:
      background_ = QPixmap(":/orange");
      shape_ = {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
      break;
    case SQUARE:
      SIZE_X = 4;
      SIZE_Y = 3;
      background_ = QPixmap(":/yellow");
      shape_ = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
      break;
    case STEP_UP_LEFT:
      background_ = QPixmap(":/green");
      shape_ = {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}};
      break;
    case STEP_UP_RIGHT:
      background_ = QPixmap(":/red");
      shape_ = {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}};
      break;
    case PYRAMID:
      background_ = QPixmap(":/light-blue");
      shape_ = {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}};
      break;
    case NUMBER_OF_TETROMINOS:
    default:
      shape_ = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  }
}

Tetromino::~Tetromino() {
  for (Block block : blocks_) {
    if (block != nullptr) {
      block->setActive(false);
    }
  }
}

bool Tetromino::moveTo(const Directions& direction) {
  return moveTo(Coords(direction));
}

bool Tetromino::moveTo(const Coords& c) {
  move(c);

  bool validMove = true;
  for (Block block : blocks_) {
    /// Check that none of the blocks cross boundaries
    if (!block->isPossibleMove()) {
      validMove = false;
      break;
    }

    /// Check that there is not a non active block in current block position
    for (Block gridBlock : w_->blocks()) {
      if (!gridBlock->getActive() && gridBlock->isCollidingWith(block)) {
        validMove = false;
        break;
      }
    }
  }

  if (!validMove) {
    /// if not a valid move, move the block back
    move(Coords(0, 0) - c);
  }

  return validMove;
}

void Tetromino::rotate(const int& direction) {
  for (Block block : blocks_) {
    block->rotate(centerBlock_, direction);
  }
}

void Tetromino::rotateIfAble(const int& direction) {
  rotate(direction);
  int temp = rotation_ + direction;
  RotationState nextState = RotationState(temp > 3 ? 0 : temp < 0 ? 3 : temp);

  Dataset data = normalDataset;
  if (type_ == HORIZONTAL) {
    data = IBlockDataset;
  } else if (type_ == SQUARE) {
    data = OBlockDataset;
  }

  /// Run the super rotation offset tests
  for (int i = 0; i < (int)data.at(SPAWN).size(); i++) {
    Coords offset = data.at(rotation_).at(i) - data.at(nextState).at(i);
    if (moveTo(offset)) {
      rotation_ = nextState;
      return;
    }
  }

  rotate(direction * -1);
}

void Tetromino::clear() {
  for (Block block : blocks_) {
    delete block;
  }
  blocks_.clear();
}

void Tetromino::move(const Coords& c) {
  for (Block block : blocks_) {
    block->move(c);
  }
  pos_ = pos_ + c;
}

void Tetromino::setPos(const Coords& pos) { pos_ = pos; }

std::vector<Block> Tetromino::blocks() const { return blocks_; }

void Tetromino::render() {
  clear();

  /// Initialize the blocks_ in correct position according to the shape
  for (int y = 0; y < SIZE_Y; y++) {
    for (int x = 0; x < SIZE_X; x++) {
      if (shape_.at(y).at(x)) {
        Block block = new Square(pos_.x + x, pos_.y + y, background_);

        if (y == centerBlockPosition_.y && x == centerBlockPosition_.x) {
          centerBlock_ = block;
        }

        blocks_.push_back(block);
      }
    }
  }
}
