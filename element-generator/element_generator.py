#! /usr/bin/python3

import os
import argparse

from jinja2 import Environment, FileSystemLoader


def create_element(config, env):
    header = env.get_template(f'src/gst{config["inherit"]}.h')
    header_output = header.render(config)

    source = env.get_template(f'src/gst{config["inherit"]}.c')
    source_output = source.render(config)

    cmake = env.get_template('CMakeLists.txt')
    cmake_output = cmake.render(config)

    dir_path = os.path.dirname(os.path.realpath(__file__))
    with open(f'{dir_path}/output/{config["elementname"]}/src/gst{config["elementname"]}.h', 'w') as header_file:
        header_file.write(header_output)
    with open(f'{dir_path}/output/{config["elementname"]}/src/gst{config["elementname"]}.c', 'w') as source_file:
        source_file.write(source_output)
    with open(f'{dir_path}/output/{config["elementname"]}/CMakeLists.txt', 'w') as cmake_file:
        cmake_file.write(cmake_output)

def create_output_tree(config):
    dir_path = os.path.dirname(os.path.realpath(__file__))
    os.makedirs(f'{dir_path}/output/{config["elementname"]}/src', exist_ok=True)

def create_config(args):
    element_name_parts = args.element_name.split('_')
    args.elementname = ''.join(element_name_parts)
    args.ELEMENT_NAME = args.element_name.upper()
    args.ElementName = ''.join([word.capitalize() for word in element_name_parts])
    return vars(args)

def parse_args():
    parser = argparse.ArgumentParser(description='List the content of a folder')

    parser.add_argument('element_name', help='The name of the element you want to create')
    parser.add_argument('element_description', help='The description of the element you want to create')
    parser.add_argument('-i', '--inherit', action='store_const', const='transform', default='element', help='Inherit from BaseTransform')
    parser.add_argument('--package-version', default="1.14.5", help="Version of gstreamer")
    parser.add_argument('--license', default="LGPL", help="The license you are using")
    parser.add_argument('--package-name', default="Yishai's Gstreamer Elements (Ubuntu 18 arm64)", help="Name of linux package")
    parser.add_argument('--package-origin', default="https://github.com/yishai1999/gstreamer", help="URL to the element repo")
    parser.add_argument('--package', default="gst-plugins-yishai", help="Name of the linux module")
    parser.add_argument('--author', default="Yishai Jaffe <yishai1999@gmail.com>", help="Name and email of the element author")

    return parser.parse_args()

def main(args):
    file_loader = FileSystemLoader('template')
    env = Environment(loader=file_loader)
    config = create_config(args)
    create_output_tree(config)
    create_element(config, env)


if __name__ == '__main__':
    main(parse_args())
