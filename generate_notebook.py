#!/usr/bin/python

import subprocess

if __name__ == "__main__":
    section_name = None
    sections = []
    code_dir = 'code'
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

    html = ''
    for (section_name, subsections) in sections:
        enscript_options = ["enscript", "-E", "--color", "--language=html", "-o -"]
        filenames = [code_dir + '/' + filename for (filename, _) in subsections]
        section_html = subprocess.check_output(enscript_options + filenames)