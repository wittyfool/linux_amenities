#!/usr/bin/env python3
import argparse
import sys
import xlrd
import csv

parser = argparse.ArgumentParser()
parser.add_argument("<xlsfile>", help="specify xls file", type=str)
parser.parse_args()

#print( sys.argv[0] )
print( "Reading xlsfile: " + sys.argv[1] )

def csv_from_excel():
    wb = xlrd.open_workbook( sys.argv[1] )
    sheet = wb.sheet_by_index(0)

    # csv_file = open('dst.csv', 'w', encoding='utf8')
    csv_file = sys.stdout

    wr = csv.writer(csv_file, quoting=csv.QUOTE_ALL)

    for row_index in range(sheet.nrows):
        wr.writerow(sheet.row_values(row_index))

    if csv_file is not sys.stdout:
        csv_file.close()

csv_from_excel()
