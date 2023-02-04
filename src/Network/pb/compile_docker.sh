#!/bin/sh
protoc --cpp_out=opt/vss-vision/src/Network/ opt/vss-vision/src/Network/pb/messages_robocup_ssl_geometry.proto
protoc --cpp_out=opt/vss-vision/src/Network/ opt/vss-vision/src/Network/pb/messages_robocup_ssl_detection.proto
protoc --cpp_out=opt/vss-vision/src/Network/ opt/vss-vision/src/Network/pb/wrapper.proto

