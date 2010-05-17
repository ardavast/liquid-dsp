/*
 * Copyright (c) 2007, 2008, 2009, 2010 Joseph Gaeddert
 * Copyright (c) 2007, 2008, 2009, 2010 Virginia Polytechnic
 *                                      Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

//
// htmlgen.c : html documentation generator
//
// rules:
//  * comments begin with '%'
//  * tilda character '~' is a space
//  * environment tokens begin with "\begin" or "\end"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liquid.doc.h"

// token table
htmlgen_token_s htmlgen_token_tab[] = {
    {"\\begin",         htmlgen_token_parse_begin},
    {"\\end",           htmlgen_token_parse_end},
    {"document",        htmlgen_token_parse_document},
    {"section",         htmlgen_token_parse_section},
    {"subsection",      htmlgen_token_parse_subsection},
    {"subsubsection",   htmlgen_token_parse_subsubsection},
    {"figure",          htmlgen_token_parse_figure},
    {"tabular",         htmlgen_token_parse_tabular},
    {"enumerate",       htmlgen_token_parse_enumerate},
    {"itemize",         htmlgen_token_parse_itemize},
};

// parse LaTeX file
void htmlgen_parse_latex_file(FILE * _fid_tex,
                              FILE * _fid_html)
{
    // write header, footer
    htmlgen_html_write_header(_fid_html);
    fprintf(_fid_html,"<h1>liquid documentation</h1>\n");
    htmlgen_html_write_footer(_fid_html);

    FILE * fid_eqn = NULL;      // equation

    // equation
    fid_eqn = fopen("html/eqn/eqn0001.tex","w");
    if (!fid_eqn) {
        fprintf(stderr,"error, could not open html/eqn/eqn0001.tex for writing\n");
        exit(1);
    }
    fprintf(fid_eqn,"\\documentclass{article} \n");
    fprintf(fid_eqn,"\\usepackage{amsmath}\n");
    fprintf(fid_eqn,"\\usepackage{amsthm}\n");
    fprintf(fid_eqn,"\\usepackage{amssymb}\n");
    fprintf(fid_eqn,"\\usepackage{bm}\n");
    fprintf(fid_eqn,"\\newcommand{\\mx}[1]{\\mathbf{\\bm{#1}}} %% Matrix command\n");
    fprintf(fid_eqn,"\\newcommand{\\vc}[1]{\\mathbf{\\bm{#1}}} %% Vector command \n");
    fprintf(fid_eqn,"\\newcommand{\\T}{\\text{T}}              %% Transpose\n");
    fprintf(fid_eqn,"\\pagestyle{empty} \n");
    fprintf(fid_eqn,"\\begin{document} \n");
    fprintf(fid_eqn,"\\newpage\n");
    fprintf(fid_eqn,"\\[ y = \\int_0^\\infty \\gamma^2 \\cos(x) dx \\]\n");
    fprintf(fid_eqn,"\\end{document}\n");
    fclose(fid_eqn);
}

// Write output html header
void htmlgen_html_write_header(FILE * _fid)
{
    fprintf(_fid,"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n");
    fprintf(_fid,"\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n");
    fprintf(_fid,"<!-- auto-generated file, do not edit -->\n");
    fprintf(_fid,"<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\">\n");
    fprintf(_fid,"<head>\n");
    fprintf(_fid,"<!-- <style type=\"text/css\" media=\"all\">@import url(http://computing.ece.vt.edu/~jgaeddert/web.css);</style> -->\n");
    fprintf(_fid,"<title>jgaeddert</title>\n");
    fprintf(_fid,"<meta name=\"description\" content=\"Gaeddert Virginia Tech\" />\n");
    fprintf(_fid,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\n");
    fprintf(_fid,"<!-- <link rel=\"Shortcut Icon\" type=\"image/png\" href=\"img/favicon.png\" /> -->\n");
    fprintf(_fid,"</head>\n");
    fprintf(_fid,"<body>\n");
}

// Write output html footer
void htmlgen_html_write_footer(FILE * _fid)
{
    fprintf(_fid,"    <!--\n");
    fprintf(_fid,"    <p>\n");
    fprintf(_fid,"    Validate:\n");
    fprintf(_fid,"    <a href=\"http://validator.w3.org/check?uri=https://ganymede.ece.vt.edu/\">XHTML 1.0</a>&nbsp;|\n");
    fprintf(_fid,"    <a href=\"http://jigsaw.w3.org/css-validator/check/referer\">CSS</a>\n");
    fprintf(_fid,"    </p>\n");
    fprintf(_fid,"    -->\n");
    fprintf(_fid,"    <p>Last updated: <em> ... </em></p>\n");
    fprintf(_fid,"</body>\n");
    fprintf(_fid,"</html>\n");
}

