#!/bin/bash

echo "Getting files..."

curl -L# -o full_data_sets.tgz https://uchicago.box.com/shared/static/5gi0wo73sd9zwowgiy7oozczzr9h2ugt.tgz

echo "Unbundling files..."

tar -xzf full_data_sets.tgz

rm full_data_sets.tgz