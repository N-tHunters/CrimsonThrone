import sys
import os

restricted_folders = ('include', 'src', 'docs', 'lib', 'resources', 'scripts')

def scan_dir(dir, structure_name=''):
    global strucure, queue
    
    for filename in os.listdir(dir):
        full_path = os.path.join(dir, filename)
        if filename.startswith('.'):
            continue
        if os.path.isdir(full_path) and filename not in restricted_folders:
            structure[structure_name].append((1, full_path))
            if not full_path in structure.keys():
                structure[full_path] = []
                queue.append(full_path)
        else:
            if filename.endswith('.cpp') or filename.endswith('.h'):
                structure[structure_name].append((0, full_path))


def get_name(path):
    name = os.path.basename(path)
    name = name[0].upper() + name[1:]
    return name


def scan_subpackage(subp, path, l=0):
    global packages, package_files, structure
    package_info[subp] = l
    packages[(subp, path)] = []
    package_files[subp] = []
    for isdir, d in structure[path]:
        if isdir:
            pname = get_name(d)
            packages[(subp, path)].append((pname, d))
            scan_subpackage(pname, d, l+1)
        else:
            package_files[subp].append(d)


def generate_subpackages():
    global packages, package_files, structure
    c_packages = dict(packages)
    for p_name, p_path in c_packages:
        scan_subpackage(p_name, p_path)
    

            
if len(sys.argv) < 2:
    print('Usage:')
    print('\t', sys.argv[0], '<target directory>')
    exit(1)

target_dir = os.path.abspath(sys.argv[1])

structure = {}

structure[target_dir] = []
queue = [target_dir]

while len(queue) > 0:
    d = queue[0]
    queue.pop(0)
    scan_dir(d, d)

package_info = {}

packages = {}
package_files = {}

for isdir, package in structure[target_dir]:
    if not isdir:
        continue
    name = get_name(package)
    packages[(name, package)] = []
    package_files[name] = []

generate_subpackages()

relations = []

def generate_classes_text(path, pref=''):
    global relations
    text = ''
    with open(path) as f:
        lines = [i.strip() for i in f.readlines()]
        i = 0
        while i < len(lines):
            line = lines[i]
            if line.startswith('class') and not line.endswith(';'):
                class_name = line.replace(':', ' ').replace('{', ' ').split()[1]
                text += pref + "class " +  class_name + " {\n"

                if ':' in line:
                    s_name = line.split(':')[1].replace('{', ' ').split()[1]
                    relations.append((0, s_name, class_name))
                j = i + 1
                while j < len(lines):
                    cline = lines[j].strip()
                    j += 1
                    if cline == '':
                        continue                        
                    if cline == '};':
                        break
                
                text += pref + '}\n'
                i = j - 1
            i += 1
    return text

def generate_package_text(path, package, level=0):
    text = ""
    pref = "  " * level
    npref = pref + "  "

    text += pref + "package " + package + " {\n"

    for subp, spath in packages[(package, path)]:
        text += generate_package_text(spath, subp, level+1)

    for fpath in package_files[package]:
        text += generate_classes_text(fpath, npref)

    text += pref + "}\n\n"

    return text


## Generate output
result = "@startuml\n\n"

for package, path in packages:
    if package_info[package] != 0:
        continue
    result += generate_package_text(path, package)

for t,a,b in relations:
    result += a + " <|-- " + b + "\n"
    
result += "\n@enduml"

print(result)
