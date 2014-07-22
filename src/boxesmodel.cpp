#include "boxesmodel.h"

#include "tile.h"

#include <QDebug>

BoxesModel::BoxesModel(QObject *parent) :
    QObject(parent),
    mRows(3),
    mColumns(3),
    mPlayers(2),
    mCurrentPlayer(1)
{
    for (int i = 0; i < mRows * mColumns; ++i)
        mTiles.append(new Tile());

    for (int i = 0; i < (mRows - 1) * (mColumns - 1); ++i)
        mOwners.append(0);

    for (int i = 0; i < mPlayers; ++i)
        mPoints.append(0);

    connect(this, SIGNAL(ownersChanged()), SLOT(checkIfWin()));
}

BoxesModel::BoxesModel(int rows, int columns, QObject *parent) :
    QObject(parent),
    mRows(rows),
    mColumns(columns),
    mPlayers(2),
    mCurrentPlayer(1)
{
    for (int i = 0; i < mRows * mColumns; ++i)
        mTiles.append(new Tile());

    for (int i = 0; i < (mRows - 1) * (mColumns - 1); ++i)
        mOwners.append(0);

    for (int i = 0; i < mPlayers; ++i)
        mPoints.append(0);
}

QObjectList BoxesModel::tiles() const
{
    return mTiles;
}

QList<int> BoxesModel::owners() const
{
    return mOwners;
}

QList<int> BoxesModel::points() const
{
    return mPoints;
}

int BoxesModel::rows() const
{
    return mRows;
}

void BoxesModel::setRows(int rows)
{
    if (mRows == rows)
        return;

    mRows = rows;
    rowsChanged();
    cleanTilesModel();
}

int BoxesModel::columns() const
{
    return mColumns;
}

void BoxesModel::setColumns(int columns)
{
    if (mColumns == columns)
        return;

    mColumns = columns;
    columnsChanged();
    cleanTilesModel();
}

int BoxesModel::players() const
{
    return mPlayers;
}

void BoxesModel::setPlayers(int players)
{
    if (mPlayers == players)
        return;

    mPlayers = players;
    emit playersChanged();
}

int BoxesModel::currentPlayer() const
{
    return mCurrentPlayer;
}

void BoxesModel::setCurrentPlayer(int currentPlayer)
{
    if (mCurrentPlayer == currentPlayer)
        return;

    mCurrentPlayer = currentPlayer;
    emit currentPlayerChanged();
}

void BoxesModel::updateValue(int index, int value)
{
    bool completed = false;
    /// TODO: Set owner for both lines, check for completion
    // qDebug() << "INDEX" << index << "VALUE" << value;

    Tile *tile1 = qobject_cast<Tile*>(mTiles.at(index));
    switch (value) {
    case Tile::UpWall:
        if (index > mColumns - 1) {
            tile1->setActiveWalls(tile1->activeWalls() + Tile::UpWall);

            Tile *tile2 = qobject_cast<Tile*>(mTiles.at(index - mColumns));
            tile2->setActiveWalls(tile2->activeWalls() + Tile::DownWall);

            /// Check if completed
            if (tile1->activeWalls() & Tile::RightWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index - mColumns + 1));

                if ((tile2->activeWalls() & Tile::LeftWall) && (tile2->activeWalls() & Tile::DownWall)) {
                    completed = true;
                    mOwners[index - mColumns - (index / mColumns) + 1] = mCurrentPlayer;
                    emit ownersChanged();
                }
            }

            if (tile1->activeWalls() & Tile::LeftWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index - mColumns - 1));

                if ((tile2->activeWalls() & Tile::RightWall) && (tile2->activeWalls() & Tile::DownWall)) {
                    completed = true;
                    mOwners[index - mColumns - (index / mColumns)] = mCurrentPlayer;
                    emit ownersChanged();
                };
            }
        }
        break;
    case Tile::RightWall:
        if (index % mColumns < mColumns - 1) {
            tile1->setActiveWalls(tile1->activeWalls() + Tile::RightWall);

            Tile *tile2 = qobject_cast<Tile*>(mTiles.at(index + 1));
            tile2->setActiveWalls(tile2->activeWalls() + Tile::LeftWall);

            /// Check if completed
            if (tile1->activeWalls() & Tile::UpWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index - mColumns + 1));

                if ((tile2->activeWalls() & Tile::LeftWall) && (tile2->activeWalls() & Tile::DownWall)) {
                    completed = true;
                    mOwners[index - mColumns - (index / mColumns) + 1] = mCurrentPlayer;
                    emit ownersChanged();
                }
            }

            if (tile1->activeWalls() & Tile::DownWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index + mColumns + 1));

                if ((tile2->activeWalls() & Tile::LeftWall) && (tile2->activeWalls() & Tile::UpWall)) {
                    completed = true;
                    mOwners[index - (index / mColumns)] = mCurrentPlayer;
                    emit ownersChanged();
                };
            }
        }
        break;
    case Tile::DownWall:
        if (index + mColumns < mTiles.length()) {
            tile1->setActiveWalls(tile1->activeWalls() + Tile::DownWall);

            Tile *tile2 = qobject_cast<Tile*>(mTiles.at(index + mColumns));
            tile2->setActiveWalls(tile2->activeWalls() + Tile::UpWall);

            /// Check if completed
            if (tile1->activeWalls() & Tile::RightWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index + mColumns + 1));

                if ((tile2->activeWalls() & Tile::LeftWall) && (tile2->activeWalls() & Tile::UpWall)) {
                    completed = true;
                    mOwners[index - (index / mColumns)] = mCurrentPlayer;
                    emit ownersChanged();
                }
            }

            if (tile1->activeWalls() & Tile::LeftWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index + mColumns - 1));

                if ((tile2->activeWalls() & Tile::RightWall) && (tile2->activeWalls() & Tile::UpWall)) {
                    completed = true;
                    mOwners[index - 1 - (index / mColumns)] = mCurrentPlayer;
                    emit ownersChanged();
                };
            }
        }
        break;
    case Tile::LeftWall:
        if (index % mColumns > 0) {
            tile1->setActiveWalls(tile1->activeWalls() + Tile::LeftWall);

            Tile *tile2 = qobject_cast<Tile*>(mTiles.at(index - 1));
            tile2->setActiveWalls(tile2->activeWalls() + Tile::RightWall);

            /// Check if completed

            if (tile1->activeWalls() & Tile::UpWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index - mColumns - 1));

                if ((tile2->activeWalls() & Tile::RightWall) && (tile2->activeWalls() & Tile::DownWall)) {
                    completed = true;
                    mOwners[index - (index / mColumns) - mColumns] = mCurrentPlayer;
                    emit ownersChanged();
                }
            }

            if (tile1->activeWalls() & Tile::DownWall) {
                tile2 = qobject_cast<Tile*>(mTiles.at(index + mColumns - 1));

                if ((tile2->activeWalls() & Tile::RightWall) && (tile2->activeWalls() & Tile::UpWall)) {
                    completed = true;
                    mOwners[index - 1 - (index / mColumns)] = mCurrentPlayer;
                    emit ownersChanged();
                };
            }
        }
        break;
    default:
        break;
    }

    if (!completed)
        nextPlayer();
    /// TODO: change current player
}

void BoxesModel::resetGame()
{
    cleanTilesModel();
}

void BoxesModel::cleanTilesModel()
{
    if (!mTiles.isEmpty()) {
        while (!mTiles.isEmpty())
            delete mTiles.takeFirst();

        for (int i = 0; i < mRows * mColumns; ++i)
            mTiles.append(new Tile());

        emit tilesChanged();

        mOwners.clear();

        for (int i = 0; i < (mRows - 1) * (mColumns - 1); ++i)
            mOwners.append(0);

        emit ownersChanged();

        for (int i = 0; i < mPlayers; ++i)
            mPoints.append(0);

        emit pointsChanged();
    }
}

int BoxesModel::tilePosition(QObject *tile)
{
    for (int i = 0; i < mTiles.length(); ++i) {
        if (mTiles.at(i) == tile)
            return i;
    }

    return -1;
}

void BoxesModel::nextPlayer()
{
    if (mCurrentPlayer + 1 <= mPlayers)
        mCurrentPlayer++;
    else
        mCurrentPlayer = 1;

    emit currentPlayerChanged();
}

void BoxesModel::checkIfWin()
{
    mPoints.clear();

    for (int i = 0; i < mPlayers; ++i)
        mPoints.append(0);

    for (int i = 0; i < mOwners.count(); ++i) {
        if (mOwners.at(i))
            mPoints[(mOwners.at(i) - 1)]++;
    }

    int totalPoints = 0;
    int winner = 0;
    int winnerPoints = 0;

    for (int i = 0; i < mPoints.length(); ++i) {
        totalPoints += mPoints.at(i);

        if (mPoints.at(i) > winnerPoints) {
            winner = i + 1;
            winnerPoints = mPoints.at(i);
        }
    }

    if (totalPoints == (mRows - 1) * (mColumns - 1)) {
        // Game has finished
        if (mPoints.count(winnerPoints) > 1) {
            // Tie/multiple winners
            QList<int> winners;

            QList<int> points;

            foreach (int point, mPoints)
                points.append(point);


            while (points.count(winnerPoints) > 0)
                winners.append(points.takeAt(points.indexOf(winnerPoints)) + 1);

            emit playersTie(winners);
        } else {
            emit playerWins(winner);
        }
    }

    emit pointsChanged();
}
