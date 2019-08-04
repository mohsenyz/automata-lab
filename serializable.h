#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QJsonObject>

/** @brief Abstract class for serialization to json, supports both read and
   write
    @author X. XYZ, DESY
    @date March 2008
    */
class Serializable {
public:
  Serializable();
  ~Serializable();
  /**
   * @brief Writes object into jsonObject
   */
  virtual void writeJson(QJsonObject &) = 0;

  /**
   * @brief Fills the object from a jsonObject
   */
  virtual void readJson(QJsonObject &) = 0;
};

#endif // SERIALIZABLE_H
