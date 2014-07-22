#ifndef BOXESMODEL_H
#define BOXESMODEL_H

#include <QObject>

class BoxesModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObjectList tiles READ tiles NOTIFY tilesChanged)
    Q_PROPERTY(QList<int> owners READ owners NOTIFY ownersChanged)
    Q_PROPERTY(QList<int> points READ points NOTIFY pointsChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY columnsChanged)
    Q_PROPERTY(int players READ players WRITE setPlayers NOTIFY playersChanged)
    Q_PROPERTY(int currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)

public:
    explicit BoxesModel(QObject *parent = 0);
    BoxesModel(int rows, int columns, QObject *parent = 0);

    QObjectList tiles() const;
    QList<int> owners() const;
    QList<int> points() const;

    int rows() const;
    void setRows(int rows);

    int columns() const;
    void setColumns(int columns);

    int players() const;
    void setPlayers(int players);

    int currentPlayer() const;
    void setCurrentPlayer(int currentPlayer);

    Q_INVOKABLE void updateValue(int index, int value);
    Q_INVOKABLE void resetGame();

signals:
    void tilesChanged();
    void rowsChanged();
    void columnsChanged();
    void playersChanged();
    void currentPlayerChanged();
    void ownersChanged();
    void pointsChanged();
    void playerWins(int player);
    void playersTie(QList<int> players);

public slots:

private:
    QObjectList mTiles;
    QList<int> mOwners;
    QList<int> mPoints;
    int mRows;
    int mColumns;
    int mPlayers;
    int mCurrentPlayer;

    void cleanTilesModel();
    int tilePosition(QObject *tile);
    void nextPlayer();

private slots:
    void checkIfWin();
};

#endif // BOXESMODEL_H
