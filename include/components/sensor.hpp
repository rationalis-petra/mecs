#ifndef __SENSOR_H_
#define __SENSOR_H_

#include "engine.hpp"

///@addtogroup Components
///@{

/** @brief A sensor will provide information to the host agent
 *
 * @details Will collect information and store it in the 'info'
 *          field, then be able to relay it to the agent
 */

typedef enum {RadarSensor, GPSSensor, MicrophoneSensor, CameraSensor} TypeofSensor;


class Sensor : public Component {
public:
  static unsigned type_idx;
  TypeofSensor type; ///< The type of sensor - Camera, Radar, etc.
  void* info;        ///< A pointer to the information output by the sensor.
  int machine;       ///< An ID which identifies which 'machine' the sensor is a part of

  Sensor();
  ~Sensor();
};


///@}

// We also define various information types;
//typedef char Image[1024 * 720 * 3];
//
//typedef struct {
//   Vec3f position;
//    int tag;
//} RadarElement;
// use Vec3f for information of GPS
//
#endif // __SENSOR_H_
