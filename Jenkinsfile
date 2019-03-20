pipeline {

    environment {
        registry = "thearusable/nocturne"
        registryCredential = 'dockerhub'
    }

    agent {
        dockerfile {
            filename 'Dockerfile'
        }
    }

    stages {

	    //stage ('Building image') {
        //    steps{
        //        script {
        //             docker.build registry
        //        }
        //    }
        //}

        stage ('pre-analysis') {
            steps {
                sh 'echo "pre-analysis"'
		        //sh 'cppcheck --enable=all --inconclusive --verbose --xml --xml-version=2 . 2> cppcheck_report.xml'
            }
        }

        stage ('build'){
            steps {
                dir('build')
                {
                    sh 'echo "build"'
                    //sh 'cmake ..'
                    //sh 'make'
                }
            }
        }
    }
    post {
	    always {
            sh 'docker push thearusable/nocturne'
	        //publishCppcheck pattern:'cppcheck_report.xml'
	    }           
    }
}
