#pragma once
#include<QPushButton>
#include<QMouseEvent>
#include<memory>

enum CellState
{
	Mark,
	Explode,
	Closed,
	Open,
};

class Cell : public QPushButton
{
	Q_OBJECT

	friend class CellGrid;
public:
	Cell();

	Cell(QWidget* parent) : QPushButton(parent)
	{
		Init();
	}

public:
	bool HasMine() const
	{
		return m_hasMine;
	}


	CellState GetState() const
	{
		return m_state;
	}

	void ToggleFlag();

private:
	void SetMine()
	{
		m_hasMine = true;
	}

	void Show();

	void Explode();

	void SetState(CellState state)
	{
		m_state = state;
	}

	void Init();

private:
	static std::unique_ptr<QIcon> m_pDefaultIcon;
	static std::unique_ptr<QIcon> m_pExplodedMineIcon;
	static std::unique_ptr<QIcon> m_pMarkIcon;
	static std::unique_ptr<QIcon> m_pMineIcon;
	CellState m_state = Closed;
	bool m_hasMine = false;

private slots:
	void mousePressEvent(QMouseEvent* event) override;
signals:
	void Clicked(Cell& cell, Qt::MouseButton button);
	void Exploded(Cell& cell);
};
