#ifndef TILE_H
#define TILE_H

#include <QObject>

class Tile : public QObject
{
    Q_OBJECT
    Q_ENUMS(walls)

    Q_PROPERTY(bool open READ open NOTIFY openChanged)
    Q_PROPERTY(int activeWalls READ activeWalls NOTIFY activeWallsChanged)
    Q_PROPERTY(int owner READ owner WRITE setOwner NOTIFY ownerChanged)

public:
    explicit Tile(QObject *parent = 0);

    enum walls {
        UpWall = 1,
        RightWall = 2,
        DownWall = 4,
        LeftWall = 8
    };

    bool open() const;

    int activeWalls() const;
    void setActiveWalls(int walls);

    int owner() const;
    void setOwner(int owner);

signals:
    void openChanged();
    void activeWallsChanged();
    void ownerChanged();

private:
    bool mOpen;
    int mActiveWalls;
    int mOwner;

    void setOpen(bool open);
};

#endif // TILE_H
