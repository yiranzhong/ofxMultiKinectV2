/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2014 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#ifndef PACKET_PIPELINE_H_
#define PACKET_PIPELINE_H_

#include <libfreenect2/usb/transfer_pool.h>
#include <libfreenect2/rgb_packet_stream_parser.h>
#include <libfreenect2/depth_packet_stream_parser.h>
#include <libfreenect2/depth_packet_processor.h>
#include <libfreenect2/rgb_packet_processor.h>

namespace libfreenect2
{

class PacketPipeline
{
public:
  typedef libfreenect2::usb::TransferPool::DataReceivedCallback PacketParser;
  virtual ~PacketPipeline();

  virtual PacketParser *getRgbPacketParser() const = 0;
  virtual PacketParser *getIrPacketParser() const = 0;

  virtual RgbPacketProcessor *getRgbPacketProcessor() const = 0;
  virtual DepthPacketProcessor *getDepthPacketProcessor() const = 0;
};

class DefaultPacketPipeline : public PacketPipeline
{
private:
  RgbPacketStreamParser *rgb_parser_;
  DepthPacketStreamParser *depth_parser_;

  RgbPacketProcessor *rgb_processor_;
  BaseRgbPacketProcessor *async_rgb_processor_;
  DepthPacketProcessor *depth_processor_;
  BaseDepthPacketProcessor *async_depth_processor_;
public:
  DefaultPacketPipeline();
  virtual ~DefaultPacketPipeline();

  virtual PacketParser *getRgbPacketParser() const;
  virtual PacketParser *getIrPacketParser() const;

  virtual RgbPacketProcessor *getRgbPacketProcessor() const;
  virtual DepthPacketProcessor *getDepthPacketProcessor() const;
};

} /* namespace libfreenect2 */
#endif /* PACKET_PIPELINE_H_ */
