#! /usr/bin/env python

#
# Algorithm to rename files.
# Open the current directory.
# get a list of directories => dir_list
#
# for each 'dir' in 'dir_list':
#   go into the 'dir'
#   get a list of all the files => files_list
#
#   i = 1
#   for each 'file' in 'files_list':
#       rename 'file' to dir-name + '_' + i
#
import os

if __name__ == "__main__":
    main_dir = os.getcwd()

    print("Starting in Directory: %s\n" % (main_dir))

    # open main_dir and get list of all the directories
    file_list = os.listdir(main_dir)

    dir_list = filter(lambda x: os.path.isdir(os.path.join(main_dir, x)), os.listdir(main_dir))

    for name in dir_list:
        dir_path = os.path.join(main_dir, name)

        print("Chdir -> %s" % (dir_path))
        os.chdir(dir_path)

        # get a list of files in the directroy being worked in which:
        #   - doesn't start with a '.' i.e. aren't special or temporary files
        #   - are not directories
        files_list = filter((lambda x: os.path.isfile(os.path.join(dir_path, x)) and not x.startswith('.')), os.listdir(dir_path))

        #files_list = [f for f in os.listdir(dir_path) if not f.startswith('.') and os.path.isfile(f)]
        print("Files in dir: %s are:" % (name))
        print(files_list)

        i = 1
        for file_name in files_list:
            fn, ext = os.path.splitext(file_name)
            if name in fn:
                print("Not renaming %s, already contains dir name in it\n" % (file_name))
                continue
            new_name = '%s-%d%s' % (name, i, ext)
            print("Renaming: %s => %s" % (file_name, new_name))
            #os.rename(file_name, new_name)
            i = i + 1 

