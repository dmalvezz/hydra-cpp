import hydra
from hydra.utils import get_original_cwd
from omegaconf import DictConfig, OmegaConf
import os

from app import run_app_with_cfg

@hydra.main(version_base=None, config_path="config", config_name="config")
def my_experiment(cfg : DictConfig) -> None:
    config = OmegaConf.to_object(cfg)
    config['cwd'] = get_original_cwd()
    config['log_dir'] = os.getcwd()
    run_app_with_cfg(str(config))

if __name__ == "__main__":
    my_experiment()