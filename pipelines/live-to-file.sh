gst-launch-1.0 \
v4l2src device=/dev/video3 \
! queue \
! videoconvert \
! jpegenc \
! mux.video_0 \
avimux name=mux \
! filesink location=/home/yishai/Downloads/test.avi \
alsasrc \
! queue \
! audioconvert \
! audioresample \
! mux.audio_0