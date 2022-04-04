/* Arduino RDA5807M Library
 * See the README file for author and licensing information. In case it's
 * missing from your distribution, use the one here as the authoritative
 * version: https://github.com/csdexter/RDA5807M/blob/master/README
 *
 * This library is for interfacing with a RDA Microelectronics RDA5807M
 * single-chip FM broadcast radio receiver.
 * See the example sketches to learn how to use the library in your code.
 *
 * This is the main code file for the library.
 * See the header file for better function documentation.
 */

#include "lib/RDA5807M.hpp"

#include "lib/RDA5807M-private.hpp"

RDA5807M::RDA5807M(I2C_HandleTypeDef *dev) {
  this->dev = dev;
}

void RDA5807M::begin(uint8_t band) {
  setRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DHIZ | RDA5807M_FLG_DMUTE | RDA5807M_FLG_BASS | RDA5807M_FLG_SEEKUP |
                                       RDA5807M_FLG_RDS | RDA5807M_FLG_NEW | RDA5807M_FLG_ENABLE);
  updateRegister(RDA5807M_REG_TUNING, RDA5807M_BAND_MASK, band);
}

void RDA5807M::end(void) {
  setRegister(RDA5807M_REG_CONFIG, 0x00);
}

void RDA5807M::setRegister(uint8_t reg, uint16_t value) {
  uint8_t txBuffer[3] = { reg, (uint8_t)(value >> 8), (uint8_t)(value & 0x00ff) };
  HAL_I2C_Master_Transmit(this->dev, RDA5807M_I2C_ADDR_RANDOM << 1, txBuffer, 3, 10000);
}

uint16_t RDA5807M::getRegister(uint8_t reg) {
  uint8_t receivedData[2];

  HAL_I2C_Master_Transmit(this->dev, RDA5807M_I2C_ADDR_RANDOM << 1, &reg, 1, 5000);
  HAL_I2C_Master_Receive(this->dev, RDA5807M_I2C_ADDR_RANDOM << 1, receivedData, 2, 5000);

  // Wire.beginTransmission(RDA5807M_I2C_ADDR_RANDOM);
  // Wire.write(reg);
  // Wire.endTransmission(false);
  // Wire.requestFrom(RDA5807M_I2C_ADDR_RANDOM, (size_t)2, true);
  // // Don't let gcc play games on us, enforce order of execution.
  // result = (uint16_t)Wire.read() << 8;
  // result |= Wire.read();

  return (receivedData[0] << 8) | receivedData[1];
}

bool RDA5807M::volumeUp(void) {
  const uint8_t volume = getRegister(RDA5807M_REG_VOLUME) & RDA5807M_VOLUME_MASK;

  if (volume == RDA5807M_VOLUME_MASK)
    return false;
  else {
    updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, volume + 1);
    return true;
  }
}

bool RDA5807M::volumeDown(bool alsoMute) {
  const uint8_t volume = getRegister(RDA5807M_REG_VOLUME) & RDA5807M_VOLUME_MASK;

  if (volume) {
    updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, volume - 1);
    if (!(volume - 1) && alsoMute)
      // If we are to trust the datasheet, this is superfluous as a volume
      // of zero triggers mute & HiZ on its own.
      mute();
    return true;
  } else
    return false;
}

bool RDA5807M::setVolume(uint8_t volume) {
  if (volume > RDA5807M_VOLUME_MASK)
    return false;
  else {
    this->updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, volume);
    return true;
  }
}

void RDA5807M::seekUp(bool wrap) {
  updateRegister(RDA5807M_REG_CONFIG, (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK | RDA5807M_FLG_SKMODE),
                 (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK | (wrap ? 0x00 : RDA5807M_FLG_SKMODE)));
}

void RDA5807M::seekDown(bool wrap) {
  updateRegister(RDA5807M_REG_CONFIG, (RDA5807M_FLG_SEEKUP | RDA5807M_FLG_SEEK | RDA5807M_FLG_SKMODE),
                 (0x00 | RDA5807M_FLG_SEEK | (wrap ? 0x00 : RDA5807M_FLG_SKMODE)));
}

void RDA5807M::mute(void) {
  updateRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DMUTE, 0x00);
}

void RDA5807M::unMute(bool minVolume) {
  if (minVolume)
    updateRegister(RDA5807M_REG_VOLUME, RDA5807M_VOLUME_MASK, 0x1);

  updateRegister(RDA5807M_REG_CONFIG, RDA5807M_FLG_DMUTE, RDA5807M_FLG_DMUTE);
}

const uint16_t RDA5807M_BandLowerLimits[5]  = { 8700, 7600, 7600, 6500, 5000 };
const uint16_t RDA5807M_BandHigherLimits[5] = { 10800, 9100, 10800, 7600, 6500 };
const uint8_t RDA5807M_ChannelSpacings[4]   = { 100, 200, 50, 25 };

uint16_t RDA5807M::getBandAndSpacing(void) {
  uint8_t band = getRegister(RDA5807M_REG_TUNING) & (RDA5807M_BAND_MASK | RDA5807M_SPACE_MASK);
  // Separate channel spacing
  const uint8_t space = band & RDA5807M_SPACE_MASK;

  if ((band & RDA5807M_BAND_MASK) == RDA5807M_BAND_EAST &&
      !(getRegister(RDA5807M_REG_BLEND) & RDA5807M_FLG_EASTBAND65M))
    // Lower band limit is 50MHz
    band = (band >> RDA5807M_BAND_SHIFT) + 1;
  else
    band >>= RDA5807M_BAND_SHIFT;

  return ((uint16_t)space << 8 | band);
}

uint16_t RDA5807M::getFrequency(void) {
  const uint16_t spaceandband = getBandAndSpacing();

  return RDA5807M_BandLowerLimits[spaceandband & 0x00ff] +
         (getRegister(RDA5807M_REG_STATUS) & RDA5807M_READCHAN_MASK) * RDA5807M_ChannelSpacings[spaceandband >> 8] / 10;
}

bool RDA5807M::setFrequency(uint16_t frequency) {
  const uint16_t spaceandband = getBandAndSpacing();
  const uint16_t origin       = RDA5807M_BandLowerLimits[spaceandband & 0x00ff];

  // Check that specified frequency falls within our current band limits
  if (frequency < origin || frequency > RDA5807M_BandHigherLimits[spaceandband & 0x00ff])
    return false;

  // Adjust start offset
  frequency -= origin;

  const uint8_t spacing = RDA5807M_ChannelSpacings[spaceandband >> 8];

  // Check that the given frequency can be tuned given current channel spacing
  if (frequency * 10 % spacing)
    return false;

  // Attempt to tune to the requested frequency
  updateRegister(RDA5807M_REG_TUNING, RDA5807M_CHAN_MASK | RDA5807M_FLG_TUNE,
                 ((frequency * 10 / spacing) << RDA5807M_CHAN_SHIFT) | RDA5807M_FLG_TUNE);

  return true;
}

uint8_t RDA5807M::getRSSI(void) {
  return (getRegister(RDA5807M_REG_RSSI) & RDA5807M_RSSI_MASK) >> RDA5807M_RSSI_SHIFT;
}
