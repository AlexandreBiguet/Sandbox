\NeedsTexFormat{LaTeX2e}

\ProvidesClass{these-old}

\LoadClass[a4paper]{report}

%==========    packages   ==========

\RequirePackage[francais,english]{babel}
\RequirePackage[T1]{fontenc}
\RequirePackage[applemac]{inputenc}
\RequirePackage{amsmath}
\RequirePackage{amsfont}
\RequirePackage{amssymb}
\RequirePackage{graphicx}
\RequirePackage{multirow}
\RequirePackage{array}
\RequirePackage[top=2cm, bottom=2cm, left=2cm, right=2cm]{geometry}

\RequirePackage{appendix}
\RequirePackage{verbatim} 
\RequirePackage{dsfont}   
\RequirePackage{mathrsfs}  
\RequirePackage[dvipsnames]{xcolor}
\RequirePackage{color}

\RequirePackage{simplewick} 
\RequirePackage[%
  pdftex=true,
  colorlinks=true,
  linkcolor=black,
  citecolor=black,
  filecolor=black,
  urlcolor=black]{hyperref}

\RequirePackage{subfig}
\RequirePackage{wrapfig}
\RequirePackage{titlesec}



%=====  chapter's form ========

\titleformat{\chapter}[display]
            {\normalfont\Large\filcenter\bfseries}
            {\titlerule[1pt]%
              \vspace{1pt}%
              \titlerule
              \vspace{1pc}%
              \LARGE\MakeUppercase{\chaptertitlename} \thechapter}
            {1pc}
            {\titlerule
              \vspace{1pc}%
              \Huge}
            
            
            %======= page de garde ============
            
            % \begin{titlepage}

            %   \begin{minipage}[l]{.5\linewidth}
            %   \includegraphics[width=3cm]{lyon1.pdf}
            % \end{minipage}
            % \begin{minipage}[c]{.4\linewidth} \hfill
            %   \includegraphics[width=3cm]{ipnl.eps}
            % \end{minipage}
            %
            % \vspace{6.5cm}
            %
            %\begin{center}
            %\huge {Pouvoir prédictif des théories en physique subatomique} \\ 
            %\vspace{7pt}
            %\large Rapport de stage de Master 2 \\
            %\vspace{5pt}
            %\large Alexandre Biguet
            %
            %   \vspace{3cm}
            %
            %   \textit{ Stage effectué du 04/03/2013 au 04/07/2013 \\Institut Pluridisciplinaire Hubert Curien \\Groupe Théorie  \\ sous la direction de Jerzy Dudek}
            %
            %\end{center}
            %
            %\end{titlepage}

            
            %=========  newcommands ===========
            
            \newcommand\ds{\displaystyle}
            \newcommand\sty{\scriptstyle}
            \newcommand\ts{\textstyle}

            \newcommand{\bm}[1]{\boldsymbol{#1}} %DR as recommended by amsmath better than \mathbf

            \newcommand{\mrm}[1]{\mathrm{#1}}

            \newcommand\vep{\varepsilon} 
            \newcommand\vph{\varphi} 

            %------------------------------------------------
            % derivations et element differentiels
            %------------------------------------------------
            \newcommand{\DD}{\dd x_1 \dd x_2 \dd x'_1 \dd x'_2 \; } % differential elements shortcut 
            \newcommand{\Dd}{\dd x \, \dd x' \;} % idem
            \newcommand\dd{\mathrm{d}} %DR the differential d
            \newcommand{\dr}{\partial}	% partial derivative

            %------------------------------------------------
            % opérateurs
            %------------------------------------------------
            \newcommand\ap{{\hat{a}}^{\,+}} %DR
            \newcommand\am{{\hat{a}}^{\, }} %DR
            \newcommand{\mO}{\hat{\mathcal{O}}}
            \newcommand{\T}{\hat{T}}
            \newcommand{\V}{\hat{V}}
            \renewcommand{\H}{\hat{H}}
            \renewcommand{\t}{\hat{t}}
            \renewcommand{\v}{\hat{v}}


            %------------------------------------------------
            % notations de Dirac
            %------------------------------------------------
            \newcommand{\bra}[1]{\left\langle #1 \right|} %DR
            \newcommand{\ket}[1]{\left| #1 \right\rangle}
            \newcommand{\keta}[1]{\widetilde{\left| #1 \right\rangle }}
            \newcommand{\scap}[2]{\left\langle #1 \right|\left. \! #2 \right\rangle} % scalar product < i | j > 
            \newcommand{\rmeB}[3]{\bra{#1}#2\ket{#3}}
            \newcommand{\rmeBa}[3]{\bra{#1}#2\keta{#3}}


            
