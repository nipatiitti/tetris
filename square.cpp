#include "square.hh"

#include <QDebug>

Square::Square(double x, double y, QPixmap& background)
    : background_(background) {
  moveToPos(Coords(x, y));
}

QRectF Square::boundingRect() const { return QRectF(0, 0, BLOCK, BLOCK); }

void Square::paint(QPainter* painter, const QStyleOptionGraphicsItem*,
                   QWidget*) {
  QRectF target(0, 0, BLOCK, BLOCK);
  QRectF source(0, 0, background_.width(), background_.height());
  painter->drawPixmap(target, background_, source);
}

bool Square::isCollidingWith(Block block, const Directions& direction) {
  Coords moveTo(direction);

  if (pos_.x - moveTo.x == block->gridPos().x &&
      pos_.y - moveTo.y == block->gridPos().y) {
    return true;
  }

  return false;
}

bool Square::isCollidingWith(Block block) { return pos_ == block->gridPos(); }

void Square::rotate(Block centerBlock, const int& direction) {
  /// Get position relative to the center block
  Coords relativePos(centerBlock->gridPos() - pos_);
  /// Calculate the new relative position
  Coords newRelativePos((direction * relativePos.y),
                        (-1 * direction * relativePos.x));

  /// Move to the new absolute position
  moveToPos(Coords(centerBlock->gridPos() + newRelativePos));
}

void Square::moveToPos(const Coords& c) {
  setX(c.x * BLOCK);
  setY(c.y * BLOCK);
  pos_ = c;
}

void Square::move(const Coords& moveTo) { moveToPos(pos_ + moveTo); }

bool Square::isPossibleMove() {
  return pos_.x < COLUMNS && pos_.x >= 0 && pos_.y >= 0 && pos_.y < ROWS;
}

Coords Square::gridPos() { return pos_; }

bool Square::getActive() const { return active; }

void Square::setActive(const bool& value) { active = value; }
