#!/bin/bash

pass() {
	echo "✅ Test PASÓ"
}

fail() {
	echo "❌ Test FALLÓ"
}

run_test() {
	description=$1
	cmd=$2
	expected=$3
	outfile=$4

	rm -f "$outfile"

	echo "📦 Test: $description"
	eval "$cmd"
	output=$(cat "$outfile" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
	expected_clean=$(echo "$expected" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

	echo "Salida: $output"
	echo "Esperado: $expected_clean"
	if [ "$output" = "$expected_clean" ]; then
		pass
	else
		fail
	fi
	echo "Código salida: $?"
	echo "---------------------------"
}

# 🧹 Limpieza inicial
rm -f outfile_*.txt infile.txt

# 📝 Crear archivo de entrada
echo -e "hola mundo\nesto es una prueba\notra línea\nhola gato\nchau mundo" > infile.txt

# 🔧 Tests obligatorios
run_test "2 comandos" \
"./pipex_bonus infile.txt \"grep hola\" \"wc -l\" outfile_2.txt" \
"2" \
"outfile_2.txt"

run_test "3 comandos" \
"./pipex_bonus infile.txt \"cat\" \"grep hola\" \"wc -w\" outfile_3.txt" \
"4" \
"outfile_3.txt"

run_test "4 comandos" \
"./pipex_bonus infile.txt \"cat\" \"tr a-z A-Z\" \"grep HOLA\" \"wc -w\" outfile_4.txt" \
"4" \
"outfile_4.txt"

run_test "5 comandos" \
"./pipex_bonus infile.txt \"cat\" \"tr a-z A-Z\" \"grep HOLA\" \"sort\" \"uniq\" outfile_5.txt" \
"HOLA GATO
HOLA MUNDO" \
"outfile_5.txt"

# 🔧 Tests here_doc
run_test "here_doc + 2 comandos" \
"printf \"hola mundo\nesto es una prueba\nFIN\n\" | ./pipex_bonus here_doc FIN \"cat\" \"wc -l\" outfile_hd2.txt" \
"2" \
"outfile_hd2.txt"

run_test "here_doc + 3 comandos" \
"printf \"hola gato\nchau perro\nhola pez\nEND\n\" | ./pipex_bonus here_doc END \"cat\" \"grep hola\" \"wc -w\" outfile_hd3.txt" \
"4" \
"outfile_hd3.txt"

run_test "here_doc + 4 comandos" \
"printf \"hola mundo\nchau\nhola gato\nSTOP\n\" | ./pipex_bonus here_doc STOP \"cat\" \"tr a-z A-Z\" \"grep HOLA\" \"wc -c\" outfile_hd4.txt" \
"21" \
"outfile_hd4.txt"