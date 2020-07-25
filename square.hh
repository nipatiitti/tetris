/**
 *  Class: Square
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that derives from the QGraphicsItem
 *
 * This class is re-implementation of the QGraphicsItem class. It is used to
 * move, rotate and draw the invidual Squares in the game
 *
 * Program author
 * @author Niilo Jaakkola
 * @date 11 May 2020
 * Student number: 292047
 * UserID: tvnija
 * E-Mail: niilo.jaakkola@tuni.fi
 *
 * */

#ifndef SQUARE_HH
#define SQUARE_HH

#include <QColor>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPen>

#include "utils.hh"

class Square : public QGraphicsItem {
 public:
  Square(double x, double y, QPixmap& background);

  /**
   * @brief boundingRect Overload for getting the QGraphicsItem bounding rect
   * @return
   */
  QRectF boundingRect() const override;

  /**
   * @brief paint Re-implementation that draws the square
   * @param painter
   * @param option
   * @param widget
   */
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  /**
   * @brief isCollidingWith Test if the @p block is in the @p direction of this
   * block
   * @param block Block to test against
   * @param direction Direction to check to
   * @return wether the blocks cllide or not
   */
  bool isCollidingWith(Block block, const Directions& direction);

  /**
   * @brief isCollidingWith test if the block is "inside" this block
   * @param block The block to test against
   * @return wether the blocks are colliding or not
   */
  bool isCollidingWith(Block block);

  /**
   * @brief rotate Move the block around the @p centerBlock according to the
   * movement matrixes
   * @param centerBlock Block to rotate around
   * @param direction Counterclockwise or clockwise
   */
  void rotate(Block centerBlock, const int& direction);

  /**
   * @brief moveToPos Move this block to the absolute position
   * @param c the new position
   */
  void moveToPos(const Coords& c);
  /**
   * @brief move Move the block to a relative position
   * @param moveTo the relative position to move to
   */
  void move(const Coords& moveTo);
  /**
   * @brief isPossibleMove Check if the block is inside the "grid" or not
   * @return
   */
  bool isPossibleMove();

  /**
   * @brief gridPos Getter for the blocks position
   * @return
   */
  Coords gridPos();

  /**
   * @brief getActive Wether the block is part of the current active tetromino
   * or not
   * @return
   */
  bool getActive() const;
  /**
   * @brief setActive Setter for the blocks activity
   * @param value
   */
  void setActive(const bool& value);

 private:
  /**
   *  @brief pos_ Blocks position
   */
  Coords pos_ = {0, 0};

  /**
   * @brief background_ The squares background image
   */
  QPixmap background_;

  /**
   * @brief active Wether the block is part of the current active tetromino
   */
  bool active = true;
};

#endif  // SQUARE_HH
