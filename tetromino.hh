/**
 *  Class: Tetromino
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single tetromino
 *
 * This class is used to hold the Squares that are currently being moved. it
 * implements helper functions for moving them, orating them etc.
 *
 * Program author
 * @author Niilo Jaakkola
 * @date 11 May 2020
 * Student number: 292047
 * UserID: tvnija
 * E-Mail: niilo.jaakkola@tuni.fi
 *
 * */

#ifndef TETROMINO_HH
#define TETROMINO_HH

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <vector>

#include "square.hh"
#include "utils.hh"

class MainWindow;

class Tetromino {
 public:
  Tetromino(const TetrominoType &type, MainWindow *w, Coords pos);
  ~Tetromino();

  /**
   * @brief render Removes the existing Squares and generates new ones based on
   * the shape
   */
  void render();

  /**
   * @brief moveTo Over load for the bool moveTo(const Coords &c)
   * @param direction
   * @return
   */
  bool moveTo(const Directions &direction);

  /**
   * @brief moveTo Moves the Tetromino to the coords if possible.
   * @param c Coordinates where to move relative to the current location
   * @return bool Wheather the movement was successfull or not
   */
  bool moveTo(const Coords &c);

  /**
   * @brief rotate Rotates the tetromino around the center block
   * @param direction Direction where to rotate. 1 for clockwise and -1 for
   * counterclock wise
   */
  void rotate(const int &direction);

  /**
   * @brief rotateIfAble Checks wether the location is possible according to the
   * super rotation system and rotates if possible
   * @param direction direction Direction where to rotate. 1 for clockwise and
   * -1 for counterclock wise
   */
  void rotateIfAble(const int &direction);

  /**
   * @brief clear Clears the blocks_ array of the tetromino
   */
  void clear();

  /**
   * @brief blocks Getter for blocks_
   * @return blocks_ array
   */
  std::vector<Block> blocks() const;

  /**
   * @brief setPos Setter for the tetrominos location pos_
   * @param pos new Coordinats relative to the tetrominos position
   */
  void setPos(const Coords &pos);

 private:
  /**
   * @brief move Moves the tetromino
   * @param c the new coordinates relative to the tetromino location
   */
  void move(const Coords &c);

  /**
   * @brief SIZE_X The size of the bounding rect of the tetromino
   */
  int SIZE_X = 3;

  /**
   * @brief SIZE_Y The size of the bounding rect of the tetromino
   */
  int SIZE_Y = 3;

  /**
   * @brief centerBlockPosition_ Coordinates of the center block
   */
  Coords centerBlockPosition_{1, 1};

  /**
   * @brief centerBlock_ Reference to the center block
   */
  Block centerBlock_ = nullptr;

  /**
   * @brief rotation_ The current rotation state of the tetromino
   */
  RotationState rotation_ = SPAWN;

  /**
   * @brief pos_ the current position of the Tetromino
   */
  Coords pos_;

  /**
   * @brief w_ Reference to the MainWindow
   */
  MainWindow *w_;

  /**
   * @brief background_ The background image for the tetromino
   */
  QPixmap background_;

  /**
   * @brief type_ The type of the tetromino
   */
  TetrominoType type_;

  /**
   * @brief shape_ Shape arrays of the tetromino. 0 is empty 1 is block
   */
  std::vector<std::vector<int>> shape_;

  /**
   * @brief blocks_ Pointer array to the Squares of the tetromino
   */
  std::vector<Block> blocks_;
};

#endif  // TETROMINO_HH
