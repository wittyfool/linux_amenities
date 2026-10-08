#!/usr/bin/env python3
"""Exchange two directories atomically using Linux renameat2()."""

import argparse
import ctypes
import os
import sys


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Atomically exchange two directories. "
            "(２つのディレクトリをアトミックに交換します)"
        ),
        add_help=False,
    )
    parser.add_argument(
        "-h", "--help", action="help",
        help="Show this help message and exit. (ヘルプを表示して終了します)",
    )
    parser.add_argument(
        "dir1", help="First directory to exchange. (交換するディレクトリ１)"
    )
    parser.add_argument(
        "dir2", help="Second directory to exchange. (交換するディレクトリ２)"
    )
    args = parser.parse_args()

    # Strip trailing slashes so a symlink cannot bypass the directory check.
    paths = [os.path.normpath(path) for path in (args.dir1, args.dir2)]
    for path in paths:
        if os.path.islink(path) or not os.path.isdir(path):
            parser.exit(1, f"実ディレクトリではありません: {path}\n")
    try:
        if os.path.samefile(*paths):
            parser.exit(1, "異なる２つのディレクトリを指定してください\n")
    except OSError as error:
        parser.exit(1, f"ディレクトリ確認失敗: {error}\n")

    libc = ctypes.CDLL(None, use_errno=True)
    try:
        exchange = libc.renameat2
    except AttributeError:
        parser.exit(1, "この環境のlibcはrenameat2に対応していません\n")

    exchange.argtypes = [
        ctypes.c_int, ctypes.c_char_p,
        ctypes.c_int, ctypes.c_char_p,
        ctypes.c_uint,
    ]
    exchange.restype = ctypes.c_int

    AT_FDCWD = -100
    RENAME_EXCHANGE = 2
    result = exchange(
        AT_FDCWD, os.fsencode(paths[0]),
        AT_FDCWD, os.fsencode(paths[1]),
        RENAME_EXCHANGE,
    )
    if result != 0:
        error = ctypes.get_errno()
        parser.exit(1, f"交換失敗: [{error}] {os.strerror(error)}\n")

    print(f"交換完了: {args.dir1} <-> {args.dir2}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
