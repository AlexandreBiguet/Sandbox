% documentclass these
% Version : 0.1
% Date    : 12 / 09 / 2014

%\NeedsTexFormat{LaTeX2e}[2014/05/01]
\ProvidesClass{these}
\LoadClass[10pts,a4paper]{report}

\RequirePackage[francais,english]{babel}
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}

\RequirePackage{amsfonts}
\RequirePackage{amssymb}
\RequirePackage{amsmath}
\RequirePackage{graphicx}
\RequirePackage{multirow}
\RequirePackage{array}
\RequirePackage[top=2cm, bottom=2cm, left=2cm, right=2cm]{geometry}
\RequirePackage{appendix}
\RequirePackage{color}
\RequirePackage{xcolor}
\RequirePackage[%
  pdftex=true,colorlinks=true,linkcolor=blue,citecolor=red,
  filecolor=green,urlcolor=yellow]{hyperref}
\RequirePackage{subfig}
\RequirePackage{wrapfig}
\RequirePackage{lineno}
\RequirePackage{enumerate}

\RequirePackage{perpage} %the perpage package
\MakePerPage{footnote} 
% the perpage package command 
% ==> permet de ré-initialiser le conteur des footnotes a chaque page



%% Boxes for C/C++ language in text
\RequirePackage{listings}
%%configuration de listings
\lstset{
language=c++,
basicstyle=\ttfamily\small, %
identifierstyle=\color{red}, %
keywordstyle=\color{blue}, %
stringstyle=\color{black!60}, %
commentstyle=\it\color{green!95!yellow!1}, %
columns=flexible, %
tabsize=2, %
extendedchars=true, %
showspaces=false, %
showstringspaces=false, %
numbers=left, %
numberstyle=\tiny, %
breaklines=true, %
breakautoindent=true, %
captionpos=b
}
\definecolor{Zgris}{rgb}{0.87,0.85,0.85}


\newsavebox{\BBbox}
\newenvironment{DDbox}[1]{
\begin{lrbox}{\BBbox}\begin{minipage}{\linewidth}}
{\end{minipage}\end{lrbox}\noindent\colorbox{Zgris}{\usebox{\BBbox}} \\
                          [.5cm]}


% Format special pour les titres des chapitres
%\titleformat{\chapter}[display]
%            {\normalfont\Large\filcenter\bfseries}
%            {\titlerule[1pt]%
%              \vspace{1pt}%
%              \titlerule
%              \vspace{1pc}%
%              \LARGE\MakeUppercase{\chaptertitlename} \thechapter
%            }
%            {1pc}
%            {\titlerule
%              \vspace{1pc}%
%              \Huge}

 
% voir les subsubsection dans la tdm
 \setcounter{tocdepth}{3}
% numerotation jusqu'au sub sub sec.
\setcounter{secnumdepth}{3}








\endinput
