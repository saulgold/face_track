#ifndef LOADEDVIDEO_H
#define LOADEDVIDEO_H
#include <QFileDialog>

class loadedVideo
{
public:
    loadedVideo();
    QFile m_filename;

private:

    void setFilename(QFile filename);
    QFile getFilename();
};

#endif // LOADEDVIDEO_H
