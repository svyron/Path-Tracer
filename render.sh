cmake --build build && \
./build/FirstImage > images/FirstImage.ppm && \
magick images/FirstImage.ppm images/FirstImage.png