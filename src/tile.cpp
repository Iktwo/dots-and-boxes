#include "tile.h"

#include <QDebug>

Tile::Tile(QObject *parent) :
    QObject(parent),
    mOpen(false),
    mActiveWalls(0), //mActiveWalls(Tile::UpWall | Tile::RightWall | Tile::DownWall | Tile::LeftWall)
    mOwner(0)
{
}

bool Tile::open() const
{
    return mOpen;
}

int Tile::activeWalls() const
{
    return mActiveWalls;
}

void Tile::setOpen(bool open)
{
    if (mOpen == open)
        return;

    mOpen = open;
    emit openChanged();
}

void Tile::setActiveWalls(int walls)
{
    /// TODO: check if now completed, if so, set owner here

    if (mActiveWalls == walls)
        return;

    mActiveWalls = walls;
    emit activeWallsChanged();

    /*qDebug() << "COMPLETED:" << (mActiveWalls & Tile::UpWall & Tile::RightWall & Tile::DownWall & Tile::LeftWall);
    if (mActiveWalls & Tile::UpWall & Tile::RightWall & Tile::DownWall & Tile::LeftWall) {
        /// TODO: set owner
    }*/
}

int Tile::owner() const
{
    return mOwner;
}

void Tile::setOwner(int owner)
{
    if (mOwner == owner)
        return;

    mOwner = owner;
    emit ownerChanged();
}
