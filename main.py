import os
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import json
import scipy.stats as stats
import numpy as np

DATA_DIR = "results"

files = os.listdir(DATA_DIR)
dataset_pairs = {}

for file in files:
    if file.endswith(".data.csv"):
        base_name = file.split(".")[0]
        metadata_file = f"{base_name}.metadata.json"
        if metadata_file in files:
            dataset_pairs[base_name] = {"data": file, "metadata": metadata_file}

print(f"Detected {len(dataset_pairs)} dataset pairs.")

for base_name, files in dataset_pairs.items():
    print(f"\nProcessing dataset: {base_name}")

    data_path = os.path.join(DATA_DIR, files["data"])
    data = pd.read_csv(data_path, sep=";")
    data = data.iloc[20:].reset_index(drop=True)

    for col in data.columns[1:]:
        data[col] = data[col].replace("ns", "").astype(int)

    metadata_path = os.path.join(DATA_DIR, files["metadata"])
    with open(metadata_path, "r") as f:
        metadata = json.load(f)

    hashers = metadata.get("hashers", [])

    print(f"Metadata for {base_name}:", json.dumps(metadata, indent=4))

    confidence_level = 0.95
    n = len(data)

    stats_data = {}
    for col in data.columns[1:]:
        mean = data[col].mean()
        std_dev = data[col].std()

        t_value = stats.t.ppf((1 + confidence_level) / 2, n - 1)
        margin_of_error = t_value * (std_dev / np.sqrt(n))
        ci_lower = mean - margin_of_error
        ci_upper = mean + margin_of_error

        stats_data[col] = {
            "mean": mean,
            "std_dev": std_dev,
            "margin_of_error": margin_of_error,
            "CI_lower": ci_lower,
            "CI_upper": ci_upper
        }

    t_tests = []
    for i in range(1, len(data.columns)):
        for j in range(i + 1, len(data.columns)):
            t_stat, p_value = stats.ttest_rel(data.iloc[:, i], data.iloc[:, j])
            t_tests.append({
                "name1": data.columns[i],
                "name2": data.columns[j],
                "t_stat": t_stat,
                "p_value": p_value,
            })

    print("\n=== Statistics ===")
    for key, values in stats_data.items():
        print(f"{key}:")
        print(f"  Mean: {values['mean']:.2f} ns")
        print(f"  Std Dev: {values['std_dev']:.2f} ns")
        print(f"  Margin of Error: ±{values['margin_of_error']:.2f} ns")
        print(f"  95% CI: ({values['CI_lower']:.2f}, {values['CI_upper']:.2f})\n")

    for t_test in t_tests:
        print("\n=== Paired T-Tests ===")
        print(f"tested columns: {t_test["name1"]} & {t_test["name2"]}")
        print(f"t-statistic: {t_test["t_stat"]:.4f}")
        print(f"p-value: {t_test["p_value"]:.4f}")

    sns.set_theme(style="whitegrid")
    plt.figure(figsize=(10, 6))

    for col in data.columns[1:]:
        sns.lineplot(x="replications", y=col, data=data, label=col, linewidth=2)

    plt.ylabel("Time (ns)", fontsize=12)
    plt.xlabel("Replications", fontsize=12)
    plt.title(f"Performance Over Replications ({base_name})", fontsize=14, fontweight="bold")
    plt.legend(title="Hashing Functions", bbox_to_anchor=(1.05, 1), loc="upper left")
    plt.xlim(21, data["replications"].max())
    plt.tight_layout()
    plt.show()


    box_plot_data = [data[col] for col in data.columns[1:]]
    box_plot_labels = [hasher["hashType"] for hasher in metadata["hashers"]]

    plt.figure(figsize=(10, 6))
    plt.boxplot(box_plot_data, tick_labels=box_plot_labels)
    plt.ylabel("Time (ns)", fontsize=12)
    plt.xlabel("Hashing Functions", fontsize=12)
    plt.title(f"Hasher Performance ({base_name}): {metadata["hashers"][0]["map size"]} of {metadata["hashers"][0]["generator"]}", fontsize=14, fontweight="bold")
    plt.xticks(rotation=45, ha="right")
    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.show()
    print("Dataset finished")

print("\n✅ Processing complete for all datasets.")
