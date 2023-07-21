---
title: graph data
author: badger code
header-includes: |
	\usepackage{tikz,pgfplots}
	\usepackage{fancyhdr}
	\pagestyle{fancy}
	\fancyhead[CO,CE]{graph data}
	\fancyfoot[CO,CE]{badger code \& radiated gamer}
	\fancyfoot[LE,RO]{\thepage}
abstract: \centering{graph data for "ascii odyssey".}
---

\newpage

\newcommand{\playerHealthMax}{100}
\newcommand{\playerDamage}{10}

\newcommand{\improvement}[1]{
	((20*#1)+\playerHealthMax)+
	((10*#1)+\playerDamage)
}
\newcommand{\adversity}[1]{
	((156.1*#1)-214)+
	((14*#1)-6.857)
}

\begin{tikzpicture}
	\begin{axis}[
		title={improvement vs. adversity},
		axis lines=left,
		xlabel={round},
		ylabel={\(f(x)\)},
		legend pos=north west,
		ymajorgrids=true,
		grid style=dashed
	]
		\addplot[
			domain=1:7,
			samples=100,
			color=red
		]
		{\improvement{x}};
		\addlegendentry{improvement}
		\addplot[
			domain=1:7,
			samples=10,
			color=blue
		]
		{\adversity{x}};
		\addlegendentry{adversity}
		\addplot[
			domain=1:7,
			samples=10,
			color=black
		]
		{abs((\improvement{x})-(\adversity{x}))};
		\addlegendentry{difficulty}
	\end{axis}
\end{tikzpicture}