#!/usr/bin/python
import subprocess
code_dir = "code"
title = "Stanford ACM-ICPC Team Notebook"

def add_toc(html, sections):
    html2 = ''
    for l in html.splitlines():
        html2 += l + '\n'
        if l == "<A NAME=\"top\">":
            html2 += "<CENTER><H1><U>" + title + "</U></H1></CENTER>\n"
            html2 += "<H1>Table of Contents</H1>\n"
            cnt = 1
            for (section_name, subsections) in sections:
                html2 += "<H2>" + section_name + "</H2>\n\n"
                html2 += "<OL START=" + str(cnt) + ">\n"
                for (_, subsection_name) in subsections:
                    html2 += "<LI><A HREF=\"#file" + str(cnt) + "\">" + subsection_name + "</A></LI>\n"
                    cnt += 1
                html2 += "</OL>\n"
            html2 += "<HR>\n"
    return html2

def get_sections():
    sections = []
    section_name = None
    with open('contents.txt', 'r') as f:
        for line in f:
            if '#' in line: line = line[:line.find('#')]
            line = line.strip()
            if len(line) == 0: continue
            if line[0] == '[':
                if section_name is not None:
                    sections.append((section_name, subsections))
                section_name = line[1:-1]
                subsections = []
            else:
                tmp = line.split('\t', 1)
                if len(tmp) == 1:
                    raise ValueError('Subsection parse error: %s' % line)
                filename = tmp[0]
                subsection_name = tmp[1]
                if subsection_name is None:
                    raise ValueError('Subsection given without section')
                subsections.append((filename, subsection_name))
    if section_name is not None:
        sections.append((section_name, subsections))
    return sections

def get_html_enscript(sections):
    enscript_options = ["enscript", "-E", "--color", "--language=html", "-o", "-", "-t", title]
    filenames = []
    for (_, subsections) in sections:
        filenames += [code_dir + '/' + filename for (filename, _) in subsections]
    bstr = subprocess.check_output(enscript_options + filenames)
    return bstr.decode('utf-8')


if __name__ == "__main__":
    sections = get_sections()
    html = get_html_enscript(sections)
    html = add_toc(html, sections)
    with open('notebook.html', 'w') as f:
        f.write(html)
