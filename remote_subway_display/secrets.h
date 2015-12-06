#ifndef SECRETS_H
#define SECRETS_H

#include <Arduino.h>

class Secrets
{
public:
  static String WIFI_SSID();
  static String WIFI_PASSWORD();
};

#endif
