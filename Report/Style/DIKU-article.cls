% This style file DIKU-article.cls was created by mofifying the style
% file njcarticle.cls provided by the Nordic Journal of Computing and 
% copyrighted by Kimmo Raatikainen. He gave me the permission to use 
% the style on 29 April 1996.
%
% Due to the changes in the LaTeX kernel a revision of this style file
% was made in April 2001.
%
%\Jyrki

\NeedsTeXFormat{LaTeX2e}[1996/12/01]
\ProvidesClass{DIKU-article-modified}%
              [2006/05/09 The article class used at DIKU]

\newcommand\@ptsize{}
\newif\if@restonecol
\newif\if@openbib
\@openbibfalse
\DeclareOption{a4paper}
   {\setlength\paperheight {297mm}%
    \setlength\paperwidth  {210mm}}
\DeclareOption{a5paper}
   {\setlength\paperheight {210mm}%
    \setlength\paperwidth  {148mm}}
\DeclareOption{b5paper}
   {\setlength\paperheight {250mm}%
    \setlength\paperwidth  {176mm}}
\DeclareOption{letterpaper}
   {\setlength\paperheight {11in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{legalpaper}
   {\setlength\paperheight {14in}%
    \setlength\paperwidth  {8.5in}}
\DeclareOption{executivepaper}
   {\setlength\paperheight {10.5in}%
    \setlength\paperwidth  {7.25in}}
\DeclareOption{landscape}
   {\setlength\@tempdima   {\paperheight}%
    \setlength\paperheight {\paperwidth}%
    \setlength\paperwidth  {\@tempdima}}
\DeclareOption{10pt}{\renewcommand\@ptsize{0}}
\DeclareOption{11pt}{\renewcommand\@ptsize{1}}
\DeclareOption{12pt}{\renewcommand\@ptsize{2}}
\DeclareOption{oneside}{\@twosidefalse \@mparswitchfalse}
\DeclareOption{twoside}{\@twosidetrue  \@mparswitchtrue}
\DeclareOption{draft}{\setlength\overfullrule{5pt}}
\DeclareOption{final}{\setlength\overfullrule{0pt}}
\DeclareOption{onecolumn}{\@twocolumnfalse}
\DeclareOption{twocolumn}{\@twocolumntrue}
\DeclareOption{leqno}{\input{leqno.clo}}
\DeclareOption{fleqn}{\input{fleqn.clo}}
\DeclareOption{openbib}{\@openbibtrue}
\ExecuteOptions{a4paper,11pt,twoside,onecolumn,final}
\ProcessOptions
\usepackage{latexsym,ifthen}
\usepackage{color}
\usepackage{graphicx}
\usepackage{url}
\usepackage[danish,english]{babel}

\renewcommand\normalsize{%
   \@setfontsize\normalsize\@xipt{13.6}%
   \abovedisplayskip 11\p@ \@plus3\p@ \@minus6\p@
   \abovedisplayshortskip \z@ \@plus3\p@
   \belowdisplayshortskip 6.5\p@ \@plus3.5\p@ \@minus3\p@
   \belowdisplayskip \abovedisplayskip
   \let\@listi\@listIDIKU}
\normalsize
\newcommand\small{%
   \@setfontsize\small\@xpt\@xiipt
   \abovedisplayskip 10\p@ \@plus2\p@ \@minus5\p@
   \abovedisplayshortskip \z@ \@plus3\p@
   \belowdisplayshortskip 6\p@ \@plus3\p@ \@minus3\p@
   \def\@listi{\leftmargin\leftmargini
               \topsep 6\p@ \@plus2\p@ \@minus2\p@
               \parsep 3\p@ \@plus2\p@ \@minus\p@
               \itemsep \parsep}%
   \belowdisplayskip \abovedisplayskip
}
\newcommand\footnotesize{%
   \@setfontsize\footnotesize\@ixpt{11}%
   \abovedisplayskip 8\p@ \@plus2\p@ \@minus4\p@
   \abovedisplayshortskip \z@ \@plus\p@
   \belowdisplayshortskip 4\p@ \@plus2\p@ \@minus2\p@
   \def\@listi{\leftmargin\leftmargini
               \topsep 4\p@ \@plus2\p@ \@minus2\p@
               \parsep 2\p@ \@plus\p@ \@minus\p@
               \itemsep \parsep}%
   \belowdisplayskip \abovedisplayskip
}
\newcommand\scriptsize{\@setfontsize\scriptsize\@viiipt{9.5}}
\newcommand\tiny{\@setfontsize\tiny\@vipt\@viipt}
\newcommand\large{\@setfontsize\large\@xiipt{14}}
\newcommand\Large{\@setfontsize\Large\@xivpt{18}}
\newcommand\LARGE{\@setfontsize\LARGE\@xviipt{22}}
\newcommand\huge{\@setfontsize\huge\@xxpt{25}}
\newcommand\Huge{\@setfontsize\Huge\@xxvpt{30}}

\setlength\parindent{12\p@}
\setlength\headheight{12\p@}
\setlength\headsep   {25\p@}
\setlength\footskip{30\p@}
\if@compatibility
  \setlength\maxdepth{4\p@}
\else
  \setlength\maxdepth{.5\topskip}
\fi
\setlength\@maxdepth\maxdepth
\setlength\textwidth{360\p@}
\setlength\textheight{208mm}
\setlength\oddsidemargin   {41.9\p@}
\setlength\evensidemargin  {46.1\p@}
\setlength\marginparwidth {100\p@}
\setlength\marginparsep{10\p@}
\setlength\marginparpush{5\p@}
\setlength\topmargin{27pt}
\setlength\footnotesep{7.7\p@}
\setlength{\skip\footins}{10\p@ \@plus 4\p@ \@minus 2\p@}
\setlength\floatsep    {12\p@ \@plus 2\p@ \@minus 2\p@}
\setlength\textfloatsep{20\p@ \@plus 2\p@ \@minus 4\p@}
\setlength\intextsep   {12\p@ \@plus 2\p@ \@minus 2\p@}
\setlength\dblfloatsep    {12\p@ \@plus 2\p@ \@minus 2\p@}
\setlength\dbltextfloatsep{20\p@ \@plus 2\p@ \@minus 4\p@}
\setlength\@fptop{0\p@ \@plus 1fil}
\setlength\@fpsep{8\p@ \@plus 2fil}
\setlength\@fpbot{0\p@ \@plus 1fil}
\setlength\@dblfptop{0\p@ \@plus 1fil}
\setlength\@dblfpsep{8\p@ \@plus 2fil}
\setlength\@dblfpbot{0\p@ \@plus 1fil}
\setlength\partopsep{3\p@ \@plus 1\p@ \@minus 1\p@}

\def\@listI{\leftmargin\leftmargini
            \parsep 4.5\p@ \@plus2\p@ \@minus\p@
            \topsep 9\p@   \@plus3\p@ \@minus5\p@
            \itemsep4.5\p@ \@plus2\p@ \@minus\p@}
\def\@listIDIKU{\leftmargin\leftmargini
            \parsep0pt
            \topsep1\p@ \@plus1\p@ \@minus1\p@
            \itemsep1\p@ \@plus1\p@ \@minus1\p@
            \partopsep0pt}

\let\@listi\@listIDIKU
\@listi
\def\@listii {\leftmargin\leftmarginii
              \labelwidth\leftmarginii
              \advance\labelwidth-\labelsep
              \topsep    2\p@ \@plus2\p@ \@minus\p@
              \parsep    0pt \itemsep   \parsep}
\def\@listiii{\leftmargin\leftmarginiii
              \labelwidth\leftmarginiii
              \advance\labelwidth-\labelsep
              \topsep    2\p@ \@plus\p@\@minus\p@
              \parsep    \z@
              \itemsep   \topsep}
\def\@listiv {\leftmargin\leftmarginiv
              \labelwidth\leftmarginiv
              \advance\labelwidth-\labelsep}
\def\@listv  {\leftmargin\leftmarginv
              \labelwidth\leftmarginv
              \advance\labelwidth-\labelsep}
\def\@listvi {\leftmargin\leftmarginvi
              \labelwidth\leftmarginvi
              \advance\labelwidth-\labelsep}
%% end of font


\setlength\lineskip{1\p@}
\setlength\normallineskip{1\p@}
\renewcommand\baselinestretch{0.95}
\setlength\parskip{0\p@ \@plus \p@}
\@lowpenalty   51
\@medpenalty  151
\@highpenalty 301

\setcounter{topnumber}{2}
\renewcommand\topfraction{.7}
\setcounter{bottomnumber}{1}
\renewcommand\bottomfraction{.5}
\setcounter{totalnumber}{3}
\renewcommand\textfraction{.1}
\renewcommand\floatpagefraction{.8}
\setcounter{dbltopnumber}{2}
\renewcommand\dbltopfraction{.7}
\renewcommand\dblfloatpagefraction{.5}
%% added
\def\draft{\overfullrule 5pt}

\mark{{}{}}
\let\pagestyle\@gobble

\newcounter{@inst}

\global\def\@institute{}
\def\institute#1{\gdef\@institute{#1}}

\global\def\institutename{\par%
  \begingroup%
  \parskip=\z@%
  \parindent=\z@%
  \setcounter{@inst}{1}%
  \def\and{\par\stepcounter{@inst}%
  \noindent$^{\the@inst}$\enspace\ignorespaces}%
  \setbox0=\vbox{\def\thanks##1{}\@institute}%
  \ifnum\c@@inst=1\relax%
  \else%
    \setcounter{footnote}{\c@@inst}%
    \setcounter{@inst}{1}%
    \noindent$^{\the@inst}$\enspace%
  \fi%
  \ignorespaces%
  \@institute\par%
  \endgroup%
}

\def\inst#1{\unskip$^{#1}$}
\def\fnmsep{\unskip$^,$}
\def\email#1{{\small\tt #1}}

\def\dates#1{\gdef\@dates{\parbox{\textwidth}{#1}}}
\dates{\writtenname{} \today.}

\def\ps@DIKUheadings{\let\@mkboth\@gobbletwo
\def\@oddhead{\hbox{}\hfil{\small\bfseries\rightmark} \hfil \rm\thepage}
\def\@oddfoot{}
\def\@evenhead{\rm \thepage\hfil{\small\bfseries\leftmark}\hfil\hbox {}}
\def\@evenfoot{}\def\sectionmark##1{}\def\subsectionmark##1{}}
%Special layout of first page
\def\ps@firstpage{\let\@mkboth\@gobbletwo
\def\@oddhead{} 
\def\@oddfoot{\scriptsize\@dates\hfill}
\let\@evenhead\@oddhead\let\@evenfoot\@oddfoot
\def\sectionmark##1{}\def\subsectionmark##1{}}  

\def\authorhead#1{\xdef\leftmark{#1}}
\def\titlehead#1{\xdef\rightmark{#1}}

\ps@DIKUheadings\pagenumbering{arabic} \onecolumn
\@twosidetrue

\newcommand\maketitle{\par
  \begingroup
    \renewcommand\thefootnote{\fnsymbol{footnote}}%
    \def\@makefnmark{\hbox to\z@{$\m@th^{\@thefnmark}$\hss}}%
    \long\def\@makefntext##1{\parindent 1em\noindent
            \hbox to1.8em{\hss$\m@th^{\@thefnmark}$}##1}%
      \newpage
      \global\@topnum\z@   % Prevents figures from going at top of page.
      \@maketitle
    \thispagestyle{firstpage}\@thanks
  \endgroup
  \setcounter{footnote}{0}%
  \let\thanks\relax
  \let\maketitle\relax\let\@maketitle\relax
  \gdef\@thanks{}\gdef\@author{}\gdef\@title{}}
\def\@maketitle{%
  \newpage
  \null
  \vskip 2em%
  \begin{center}%
    {\Large\bfseries\boldmath\pretolerance=10000
     \@title \par}%
    \vskip 1.5em%
    {\small\it
      \lineskip .5em%
      \begin{tabular}[t]{c}%
        \rm\@author
      \end{tabular}\par%
      \vskip 1em%
      {\institutename}}
  \end{center}%
  \vskip 1.5em}

\setcounter{secnumdepth}{3}
\newcounter {section}
\newcounter {subsection}[section]
\newcounter {subsubsection}[subsection]
\newcommand\thepart          {\Roman{part}}
\renewcommand\thesection       {\arabic{section}}
\renewcommand\thesubsection    {\thesection.\arabic{subsection}}
\renewcommand\thesubsubsection {\thesubsection .\arabic{subsubsection}}

\def\@part[#1]#2{\@warning{Do not use command `\string\part'}}

\newcommand\chapter[1]{\newpage%
  \null%
  \vskip 2em%
  \begin{center}%
    {\Large\bfseries\boldmath\pretolerance=10000
     #1 \par}%
    \vskip 1.5em%
  \end{center}\noindent\ignorespaces%
}

\newcommand\section{\@startsection {section}{1}{\z@}%
                                   {-3.5ex \@plus -1ex \@minus -.2ex}%
                                   {2.3ex \@plus.2ex}%
                     {\centering\reset@font\normalsize\bfseries}}
\newcommand\subsection{\@startsection{subsection}{2}{\z@}%
                                     {-3.25ex\@plus -1ex \@minus -.2ex}%
                                     {1.5ex \@plus .2ex}%
                                     {\raggedright\reset@font\normalsize\itshape}}
\newcommand\subsubsection{\@startsection{subsubsection}{3}{\z@}%
                                     {-3.25ex\@plus -1ex \@minus -.2ex}%
                                     {1.5ex \@plus .2ex}%
                                     {\raggedright\reset@font\normalsize\itshape}}
\newcommand\paragraph{\par}
\newcommand\subparagraph{\par}

  \setlength\leftmargini  {2.2em} % Original {2.5em}
\setlength\leftmarginii  {1.7em}  % {2.2em}
\setlength\leftmarginiii {1.7em}  % {1.87em}
\setlength\leftmarginiv  {1em}    % {1.7em}
  \setlength\leftmarginv  {1em}
  \setlength\leftmarginvi {1em}
\setlength\leftmargin    {\leftmargini}
\setlength  \labelsep  {.5em}
\setlength  \labelwidth{\leftmargini}
\addtolength\labelwidth{-\labelsep}
\@beginparpenalty -\@lowpenalty
\@endparpenalty   -\@lowpenalty
\@itempenalty     -\@lowpenalty

\renewcommand\theenumi{\arabic{enumi}}
\renewcommand\theenumii{\alph{enumii}}
\newcommand\labelenumi{\theenumi.}    % Original {(\theenumi)}
\newcommand\labelenumii{\theenumii)}  % {(\theenumii)}
\renewcommand\p@enumii{\theenumi}
\newcommand\labelitemi{\normalfont\bfseries --}       % {$\circ$}
\newcommand\labelitemii{$\circ$}                      % {\normalfont\bfseries --}

\def\enumerate{\ifnum \@enumdepth >1 \@toodeep\else
      \advance\@enumdepth \@ne \let\@listi\@listIDIKU
      \edef\@enumctr{enum\romannumeral\the\@enumdepth}\list
      {\csname label\@enumctr\endcsname}{\usecounter
        {\@enumctr}\def\makelabel##1{\hss\llap{##1}}}\fi}

\def\itemize{\ifnum \@itemdepth >1 \@toodeep\else
	\advance\@itemdepth \@ne \let\@listi\@listIDIKU
	\edef\@itemitem{labelitem\romannumeral\the\@itemdepth}\list
	{\csname\@itemitem\endcsname}{\def\makelabel##1{\hss\llap{##1}}}\fi}

\def\descriptionlabel#1{\hspace\labelsep \normalfont\bfseries #1}
\def\description{\let\@listi\@listIDIKU\list
	{}{\labelwidth\z@ \itemindent-\leftmargin
	\let\makelabel\descriptionlabel}}
\let\enddescription\endlist


  \newenvironment{abstract}{%
       \noindent\small {\bf\abstractname.{}\hspace\labelsep }\rm\ignorespaces}%
      {\par\vspace{1.5em}\normalsize}
\newenvironment{subject}{%
       \noindent\small{\bf \categoriesname.{}\hspace\labelsep }\rm\ignorespaces}%
      {\par\vspace{1.5em}\normalsize}

\newenvironment{keywords}{%
       \noindent\small{\bf \keywordsname.{}\hspace\labelsep }\rm\ignorespaces}%
      {\par\vspace{1.5em}\normalsize}

\newenvironment{acknowledgements}{\section*{\acknowledgementsname}}{}


\def\and{%%                             % \begin{tabular}
\end{tabular}\hskip 1em plus .17fil\begin{tabular}[t]{c}%
\small\rm%% \end{tabular}
}

\def\AND{%%                             % \begin{tabular}
\end{tabular}\vskip 12pt plus 6pt minus 4pt\begin{tabular}[t]{c}%
\small\rm%% \end{tabular} 
}

\newenvironment{verse}
               {\let\\=\@centercr
                \list{}{\itemsep      \z@
                        \itemindent   -1.5em%
                        \listparindent\itemindent
                        \rightmargin  \leftmargin
                        \advance\leftmargin 1.5em}%
                \item[]}
               {\endlist}
\newenvironment{quotation}
               {\list{}{\listparindent 1.5em%
                        \itemindent    \listparindent
                        \rightmargin   \leftmargin
                        \parsep        \z@ \@plus\p@}%
                \item[]}
               {\endlist}
\newenvironment{quote}
               {\list{}{\rightmargin\leftmargin}%
                \item[]}
               {\endlist}
\newenvironment{titlepage}
    {\@warning{Do not use environment `\string\titlepage'}}
    {\relax}
\newcommand\appendix{\par
  \setcounter{section}{0}%
  \setcounter{subsection}{0}%
  \renewcommand\thesection{\appendixname{ }\Alph{section}}}
\setlength\arraycolsep{5\p@}
\setlength\tabcolsep{6\p@}
\setlength\arrayrulewidth{.4\p@}
\setlength\doublerulesep{2\p@}
\setlength\tabbingsep{\labelsep}
\skip\@mpfootins = \skip\footins
\setlength\fboxsep{3\p@}
\setlength\fboxrule{.4\p@}

\newcounter{figure}
\let\floatsize\footnotesize
\def\fps@figure{tbp}
\def\ftype@figure{1}
\def\ext@figure{lof}
\def\fnum@figure{{\bf \figurename~\thefigure}}
\newenvironment{figure}%
               {\floatsize\@float{figure}}%
               {\end@float}
\newenvironment{figure*}%
               {\floatsize\@dblfloat{figure}}%
               {\end@dblfloat}

\newcounter{table}
\def\fps@table{tbp}
\def\ftype@table{2}
\def\ext@table{lot}
\def\fnum@table{\tablename~\thetable}
\newenvironment{table}
               {\floatsize\@float{table}}
               {\end@float}
\newenvironment{table*}
               {\floatsize\@dblfloat{table}}
               {\end@dblfloat}

\def\continued{\@makecaption{\csname fnum@\@captype\endcsname}{{\em (cont.)}}}

\newlength\abovecaptionskip
\newlength\belowcaptionskip
\setlength\abovecaptionskip{10\p@}
\setlength\belowcaptionskip{10\p@}
\long\def\@makecaption#1#2{%
  \vskip\abovecaptionskip
  \setbox\@tempboxa\hbox{\floatsize{\bf #1\@.} #2}% :
  \ifdim \wd\@tempboxa >\hsize
   {\def\baselinestretch{0.85}\floatsize{\bf #1.} #2\par}% :
  \else
    \hbox to\hsize{\hfil\box\@tempboxa\hfil}%
  \fi
  \vskip\belowcaptionskip}

\DeclareOldFontCommand{\rm}{\normalfont\rmfamily}{\mathrm}
\DeclareOldFontCommand{\sf}{\normalfont\sffamily}{\mathsf}
\DeclareOldFontCommand{\tt}{\normalfont\ttfamily}{\mathtt}
\DeclareOldFontCommand{\bf}{\normalfont\bfseries}{\mathbf}
\DeclareOldFontCommand{\it}{\normalfont\itshape}{\mathit}
\DeclareOldFontCommand{\sl}{\normalfont\slshape}{\@nomath\sl}
\DeclareOldFontCommand{\sc}{\normalfont\scshape}{\@nomath\sc}
\newcommand{\cal}{\protect\pcal}
\newcommand{\pcal}{\@fontswitch{\relax}{\mathcal}}
\newcommand{\mit}{\protect\pmit}
\newcommand{\pmit}{\@fontswitch{\relax}{\mathnormal}}

\newcommand\@pnumwidth{1.55em}
\newcommand\@tocrmarg {2.55em}
\newcommand\@dotsep{4.5}
\setcounter{tocdepth}{0}


\def\tableofcontents{\@warning{Do not use command `\string\tableofcontents'}}
\def\listoffigures{\@warning{Do not use command `\string\listoffigures'}}
\def\listoftables{\@warning{Do not use command `\string\listoftables'}}



\def\thebibliography#1{\section*{\refname}\footnotesize\list
  {[\arabic{enumi}]}{\settowidth\labelwidth{[#1]}\leftmargin\labelwidth
  \advance\leftmargin\labelsep\itemsep=0pt \parsep=0pt
  \usecounter{enumi}}
  \def\newblock{\hskip .11em plus .33em minus -.07em}
  \sloppy
  \sfcode`\.=1000\relax
}
\let\endthebibliography=\endlist
\def\@lbibitem[#1]#2{\item\if@filesw \immediate\write\@auxout
	{\string\bibcite{#2}{\the\c@enumi}}\fi\ignorespaces}

\def\alternativecitationstyle{
 \def\thebibliography##1{\section*{\refname}%\vskip-\lastskip
    \topsep=0pt \parskip=0pt \partopsep=0pt \parindent=0pt
    \hangindent=7mm \hangafter=1
    \def\newblock{\hskip .11em plus .33em minus -.07em}
    \sloppy
    \sfcode`\.=1000\relax
    \footnotesize
 }
 \def\endthebibliography{\par}
 \def\@lbibitem{\DIKU@lbibitem} \let\@internalcite\cite
 \def\@citeseppen{-1000}
 \def\cite{\let\@cite\DIKU@cite@two%
	\@ifnextchar [{\@tempswatrue\DIKU@cite}{\@tempswafalse\DIKU@cite[]}}
 \def\citet{\let\@cite\DIKU@cite@one%
	\@ifnextchar [{\@tempswatrue\DIKU@cite}{\@tempswafalse\DIKU@cite[]}}
 \def\citealt{\let\@cite\DIKU@cite@three%
	\@ifnextchar [{\@tempswatrue\DIKU@cite}{\@tempswafalse\DIKU@cite[]}}
 \def\citeauthor{\let\@cite\DIKU@cite@four\@tempswafalse%
	\@ifnextchar [{\@warning
	  {Do not use an optional argument in \string\citeauthor'}\DIKU@cite}%
	{\DIKU@cite[]}}
 \def\citeyear{\let\@cite\DIKU@cite@five\@tempswafalse%
	\@ifnextchar [{\@warning
	  {Do not use an optional argument in \string\citeyear'}\DIKU@cite}%
	{\DIKU@cite[]}}
 \def\citemul{\@ifnextchar [{\@warning
	  {Do not use an optional argument in \string\citemul'}\DIKU@citemul}%
	{\DIKU@citemul[]}}
 \let\mulcite\citemul
 \def\bibcite##1##2{\global\@namedef{b@##1}{##2}}
}

\def\DIKU@lbibitem[#1]#2{\par\hangindent=7mm \hangafter=1\if@filesw
	{ \def\protect##1{\string ##1\space}\def\etal{\string\etal}\immediate
	  \write\@auxout{\string\bibcite{#2}{#1}}}\fi\ignorespaces}
\def\DIKU@cite[#1]#2{\DIKU@citex[#1]#2,\@\@}
\def\DIKU@citex[#1]#2,#3\@\@{\def\tempa{#3}%
	\ifx\tempa\@empty \else \@warning
	  {Use multiple arguments only in `\string\mulcite'}\fi%
	\if@filesw\immediate\write\@auxout{\string\citation{#2}}\fi%
	\@ifundefined{b@#2}{\@cite{{\bf ?}}{{\bf ?}}{#1}\@warning
        {Citation `#2' on page \thepage \space undefined}}%
 	{\edef\@tempa{\@nameuse{b@#2}}\@cite{\expandafter
            \@car\@tempa \@nil\null}{\expandafter
            \@cdr\@tempa\@nil\null}{#1}}%
% 	{\@cite{\@nameuse{ba@#2}}{\@nameuse{by@#2}}{#1}}%
}
\def\DIKU@cite@one#1#2#3{#1\ [#2\ifthenelse{\boolean{@tempswa}}{, #3}{}]}
\def\DIKU@cite@two#1#2#3{[#1\ #2\ifthenelse{\boolean{@tempswa}}{, #3}{}]}
\def\DIKU@cite@three#1#2#3{#1\ #2\ifthenelse{\boolean{@tempswa}}{, #3}{}}
\def\DIKU@cite@four#1#2#3{#1}
\def\DIKU@cite@five#1#2#3{#2}

\def\DIKU@citemul[#1]#2{\DIKU@mcite #2\@\@}
\def\DIKU@mcite#1,#2\@\@{%
 	\if@filesw\immediate\write\@auxout{\string\citation{#1,#2}}\fi%
	\@ifundefined{b@#1}{{\bf ?}\@warning
        {Citation `#1' on page \thepage \space undefined}}%
 	{\edef\@tempa{\@nameuse{b@#1}}\expandafter
	 \@car\@tempa\@nil\ }\def\@citea{[}\@for\@citeb:=#1,#2\do
        {\@citea\def\@citea{,\penalty\@citeseppen\ }\@ifundefined
	{b@\@citeb}{{\bf ?}\@warning
	{Citation `\@citeb' on page \thepage \space undefined}}%
	{\edef\@tempa{\@nameuse{b@\@citeb}}\expandafter
	 \@cdr\@tempa\@nil}}]%
}

\newcommand\etal{{\noexpand\textrm{et al.}}}

\def\eqnref#1{Eq.~(\ref{#1})}
\def\figref#1{Figure~\ref{#1}}  % Original {Fig.~\ref{#1}}
\def\tableref#1{Table~\ref{#1}}

\newif\if@restonecol 
\def\theindex{\@warning{Do not use environment `\string\theindex'}}
\def\endtheindex{\relax} 

\newcommand\@idxitem  {\par\hangindent 40\p@}
\newcommand\subitem   {\par\hangindent 40\p@ \hspace*{20\p@}}
\newcommand\subsubitem{\par\hangindent 40\p@ \hspace*{30\p@}}
\newcommand\indexspace{\par \vskip 10\p@ \@plus5\p@ \@minus3\p@\relax}

\renewcommand\footnoterule{%
  \kern-3\p@
  \hrule width 0.5in
  \kern 2.6\p@}

\long\def\@makefntext#1{\parindent 0pt\noindent$^{\@thefnmark}$\enspace#1}

\newcommand\figurename{Figure}
\newcommand\tablename{Table}
\newcommand\appendixname{Appendix}
\newcommand\abstractname{Abstract}
\newcommand\categoriesname{CR Classification}
\newcommand\keywordsname{Keywords}
\newcommand\acknowledgementsname{Acknowledgements}
\newcommand\refname{References}
\newcommand\proofname{Proof}
\newcommand\theoremname{Theorem}
\newcommand\lemmaname{Lemma}
\newcommand\corollaryname{Corollary}
\newcommand\propositionname{Proposition}
\newcommand\definitionname{Definition}
\newcommand\conjecturename{Conjecture}
\newcommand\claimname{Claim}
\newcommand\invariantname{Invariant}
\newcommand\problemname{Problem}
\newcommand\examplename{Example}
\newcommand\factname{Fact}
\newcommand\remarkname{Remark}
\newcommand\observationname{Observation}
\newcommand\writtenname{Written}

\gdef\captiondanish{%
  \renewcommand\figurename{Figur}%
  \renewcommand\tablename{Tabel}%
  \renewcommand\appendixname{Bilag}%
  \renewcommand\abstractname{Resum\'e}%
  \renewcommand\categoriesname{CR klassifikation}%
  \renewcommand\keywordsname{N{\o}gleord}%
  \renewcommand\acknowledgementsname{Tak}%
  \renewcommand\refname{Litteratur}%
  \renewcommand\proofname{Bevis}%
  \renewcommand\theoremname{Teorem}%
  \renewcommand\lemmaname{Lemma}%
  \renewcommand\corollaryname{Konsekvens}%
  \renewcommand\propositionname{S{\ae}tning}%
  \renewcommand\definitionname{Definition}%
  \renewcommand\conjecturename{Konjektur}%
  \renewcommand\claimname{P{\aa}stand}%
  \renewcommand\invariantname{Invariant}%
  \renewcommand\problemname{Problem}%
  \renewcommand\examplename{Eksempel}%
  \renewcommand\factname{Faktum}%
  \renewcommand\remarkname{Bem{\ae}rkning}%
  \renewcommand\observationname{Observation}%
  \renewcommand\writtenname{Skrevet}%
}

\newcommand\today{\number\day\space%
  \ifcase\month\or
  January\or February\or March\or April\or May\or June\or
  July\or August\or September\or October\or November\or December\fi
  \space\number\year}

\def\selectdanish{%
  \input danish.ldf\relax
  \captiondanish\relax
  \datedanish\relax
  \extrasdanish
}

\setlength\columnsep{10\p@}
\setlength\columnseprule{0\p@}


\def\@startsection#1#2#3#4#5#6{\if@noskipsec\gdef\@period{} \leavevmode
  \gdef\@period{.} \fi
   \par \@tempskipa #4\relax
   \@afterindenttrue
   \ifdim \@tempskipa <\z@ \@tempskipa -\@tempskipa \@afterindentfalse\fi
   \if@nobreak \everypar{}\else
     \addpenalty{\@secpenalty}\addvspace{\@tempskipa}\fi \@ifstar
     {\@ssect{#3}{#4}{#5}{#6}}{\@dblarg{\@sect{#1}{#2}{#3}{#4}{#5}{#6}}}}

\def\@sect#1#2#3#4#5#6[#7]#8{\ifnum #2>\c@secnumdepth
     \def\@svsec{}\else 
     \refstepcounter{#1}\edef\@svsec{\csname the#1\endcsname\ifnum
     #2=1.\fi\hskip 0.5em }\fi %original had a space after .
     \@tempskipa #5\relax
      \ifdim \@tempskipa>\z@ 
        \begingroup #6\relax
          \@hangfrom{\hskip #3\relax\@svsec}{\interlinepenalty \@M #8\par}%
        \endgroup
       \csname #1mark\endcsname{#7}\addcontentsline
         {toc}{#1}{\ifnum #2>\c@secnumdepth \else
                      \protect\numberline{\csname the#1\endcsname}\fi
                    #7}\else
        \def\@svsechd{#6\hskip #3\relax  %% \relax added 2 May 90
                   \@svsec #8\csname #1mark\endcsname
                      {#7}\addcontentsline
                           {toc}{#1}{\ifnum #2>\c@secnumdepth \else
                             \protect\numberline{\csname the#1\endcsname}\fi
                       #7}}\fi
     \@xsect{#5}}

\def\@xsect#1{\@tempskipa #1\relax
      \ifdim \@tempskipa>\z@
       \par \nobreak
       \vskip \@tempskipa
       \@afterheading
    \else \global\@nobreakfalse \global\@noskipsectrue
       \everypar{\if@noskipsec \global\@noskipsecfalse
                   \clubpenalty\@M \hskip -\parindent
                   \begingroup \@svsechd \endgroup \unskip
                   \hskip -#1\relax  % relax added 14 Jan 91
                  \else \clubpenalty \@clubpenalty
                    \everypar{}\fi}\fi\ignorespaces}


\def\twolevelnumbering#1{\@for \DIKU@countername :=#1\do{
	\@namedef{DIKU@\DIKU@countername}{\relax}\relax}\relax
}

% \DIKUnewtheorem{BODYSTYLE}{NAME}{TEXT}
\def\DIKUnewtheorem#1#2#3{\expandafter\@ifdefinable\csname #2\endcsname
{\@definecounter{#2}\@ifundefined{DIKU@#2}{%
\expandafter\xdef\csname the#2\endcsname{\@thmcounter{#2}}%
\global\@namedef{#2}{\@thm{#1}{#2}{#3}}\global\@namedef{end#2}{\@endtheorem}}{%
\@addtoreset{#2}{section}%
\expandafter\xdef\csname the#2\endcsname{\expandafter\noexpand
  \thesection \@thmcountersep \@thmcounter{#2}}%
\global\@namedef{#2}{\@thm{#1}{#2}{#3}}\global\@namedef{end#2}{\@endtheorem}}
\global\@namedef{#2*}{\@starthm{#1}{#3}}%
      \global\@namedef{end#2*}{\@endstartheorem}
}}

\def\@starthm#1#2{%
	\@ifnextchar[{\@starythm{#1}{#2}}{\@starxthm{#1}{#2}}}
\def\@starxthm#1#2{\@beginstartheorem{#2}\ignorespaces#1}
\def\@starythm#1#2[#3]{\@opargbeginstartheorem{#2}{#3}\ignorespaces#1}
\def\@beginstartheorem#1{\trivlist \item[\hskip \labelsep{\bfseries #1.}]}
\def\@opargbeginstartheorem#1#2{\trivlist
      \item[\hskip \labelsep{\bfseries #1.\ (#2)}]}
\def\@endstartheorem{\endtrivlist}

\def\@thm#1#2#3{\refstepcounter
    {#2}\@ifnextchar[{\@ythm{#1}{#2}{#3}}{\@xthm{#1}{#2}{#3}}}

\def\@xthm#1#2#3{\@begintheorem{#3}{\csname the#2\endcsname.}\ignorespaces#1}
\def\@ythm#1#2#3[#4]{\@opargbegintheorem{#3}{\csname
       the#2\endcsname.}{#4}\ignorespaces#1}
\def\@begintheorem#1#2{\trivlist \item[\hskip \labelsep{\bfseries #1\ #2}]}
\def\@opargbegintheorem#1#2#3{\trivlist
      \item[\hskip \labelsep{\bfseries #1\ #2\ (#3)}]}
\def\@endtheorem{\endtrivlist}


\def\DIKU@environments{%
\@ifundefined{DIKU@figure}{%
         \gdef\thefigure{\@arabic\c@figure}}
	{\newcounter{figure}[section]%
        \gdef\thefigure{\@arabic\c@section.\@arabic\c@figure}}
\@ifundefined{DIKU@table}{%
        \gdef\thetable{\@arabic\c@table}}
	{\newcounter{table}[section]%
        \gdef\thetable{\@arabic\c@section.\@arabic\c@table}}

\@ifundefined{DIKU@equation}{\gdef\theequation{\@arabic\c@equation}}{%
\@addtoreset{equation}{section}\gdef\theequation{%
        \@arabic\c@section.\@arabic\c@equation}}

\DIKUnewtheorem{\it}{theorem}{\theoremname}
\DIKUnewtheorem{\it}{lemma}{\lemmaname}
\DIKUnewtheorem{\it}{corollary}{\corollaryname}
\DIKUnewtheorem{\it}{proposition}{\propositionname}
\DIKUnewtheorem{\it}{definition}{\definitionname}
\DIKUnewtheorem{\it}{conjecture}{\conjecturename}
\DIKUnewtheorem{\it}{claim}{\claimname}
\DIKUnewtheorem{\it}{invariant}{\invariantname}
\DIKUnewtheorem{\rm}{problem}{\problemname}
\DIKUnewtheorem{\rm}{example}{\examplename}
\DIKUnewtheorem{\rm}{fact}{\factname}
\DIKUnewtheorem{\rm}{remark}{\remarkname}
\DIKUnewtheorem{\rm}{observation}{\observationname}

\gdef\proof{\relax{\noindent\bfseries \proofname\@. }\ignorespaces}
\gdef\endproof{\ifhmode\nobreak\qed\par\fi\medskip}
\gdef\qed{\hspace*{\fill}\raisebox{-.2ex}{$\Box$}}
}


\AtBeginDocument{\DIKU@environments
  \@colht\textheight  \@colroom\textheight \vsize\textheight
   \columnwidth\textwidth \@clubpenalty\clubpenalty
   \if@twocolumn \advance\columnwidth -\columnsep
      \divide\columnwidth\tw@ \hsize\columnwidth \@firstcolumntrue
   \fi
  \hsize\columnwidth \linewidth\hsize
%  \headwidth\textwidth
  \begingroup\@floatplacement\@dblfloatplacement
   \makeatletter\let\@writefile\@gobbletwo
   \@input{\jobname.aux}\endgroup
  \if@filesw \immediate\openout\@mainaux=\jobname.aux
    \immediate\write\@mainaux{\relax}\fi
  \@ifundefined{process@table}{\relax}{\process@table}
  \let\glb@currsize\@empty
  \gdef\twolevelnumbering#1{\@warning{Command %
        `\string\twolevelnumering' can only be used in the preamble}}
  \gdef\draft{\@warning{Command `\string\draft' %
         can only be used in the preamble}}
  \gdef\alternativecitationstyle{\@warning{Command `\string\alternativecitationstyle' %
         can only be used in the preamble}}
  \def\do#1{\let #1\@notprerr}%
%  \@preamblecmds
  \let\do\noexpand
  \@normalsize\everypar{}\@noskipsecfalse
}
\newbox\@tabbingstrutbox

\def\@startline{\global\@curtabmar\@nxttabmar\relax
   \global\@curtab\@curtabmar\global\setbox\@curline\hbox % missing \global
    {}\@startfield\@tabbingstrut}                         % added 17 Jun 86

\def\tabbingstretch{1}
\def\tabbing{\setbox\@tabbingstrutbox=\hbox{\vrule
     height \tabbingstretch \ht\strutbox
     depth \tabbingstretch \dp\strutbox
     width\z@}\lineskip \z@\let\>\@rtab\let\<\@ltab\let\=\@settab
     \let\+\@tabplus\let\-\@tabminus\let\`\@tabrj\let\'\@tablab
     \let\\=\@tabcr
     \global\@hightab\@firsttab
     \global\@nxttabmar\@firsttab
     \dimen\@firsttab\@totalleftmargin
     \global\@tabpush0 \global\@rjfieldfalse
     \trivlist \item[]\if@minipage\else\vskip\parskip\fi
     \setbox\@tabfbox\hbox{\rlap{\indent\hskip\@totalleftmargin
       \the\everypar}}\def\@itemfudge{\box\@tabfbox}\@startline\ignorespaces}

\def\@tabbingstrut{\relax\ifmmode\copy\@tabbingstrutbox\else%
    \unhcopy\@tabbingstrutbox\fi}

\endinput
%% 
%% End of file `DIKU-article.cls'.








