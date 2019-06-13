#!/usr/bin/env python3
import argparse
import sys
import xlrd
import csv

parser = argparse.ArgumentParser()
parser.add_argument("<xlsfile>", help="specify xls file", type=str)

parser.parse_args()

#print( sys.argv[0] )
print( sys.argv[1] )

def csv_from_excel():
    wb = xlrd.open_workbook( sys.argv[1] )
    sheet = wb.sheet_by_index(0)
    your_csv_file = open('dst.csv', 'w', encoding='utf8')
    wr = csv.writer(your_csv_file, quoting=csv.QUOTE_ALL)

    for row_index in range(sheet.nrows):
        #row = sheet.row(row_index)
        #print("row idx=" + str(row_index))
        wr.writerow(sheet.row_values(row_index))

    your_csv_file.close()

csv_from_excel()
